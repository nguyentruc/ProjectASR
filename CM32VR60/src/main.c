#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f1xx_hal.h"
#include "bboard_system.h"
#include "ring_buffer.h"
#include "CM32VR60.h"
#include <stdarg.h>

#define MAX_RX_BUFFER 64
#define DEBUG_MODE

uint8_t rxByte = NULL;

#if defined(DEBUG_MODE)
uint8_t rxBuffer[MAX_RX_BUFFER];
uint8_t rxIndex = 0;
uint8_t volatile cmdReceived;

rb_handle_t buffer;
#else
rb_handle_t buffer;
#endif
uint8_t operationFinished;
DMA_HandleTypeDef dma_rx_params;
I2C_HandleTypeDef i2c_handle;

void SystemClock_Config(void);
void Usart_DMA_Init(void);
void I2C_init(void);
void GPIO_init(void);
void print(const char *format, ...);
void loadModel();

int main()
{
    HAL_Init();
    bboard_led_green_init();
    bboard_led_red_init();
    SystemClock_Config();

    bboard_usart1_init(115200);

    bboard_usart1_printf("\n***CM32VR60 TEST***\nSYSCLK: %ld, HCLK: %ld,"
            " ABP1: %ld, ABP2: %ld\n",
            HAL_RCC_GetSysClockFreq(), HAL_RCC_GetHCLKFreq(),
            HAL_RCC_GetPCLK1Freq(), HAL_RCC_GetPCLK2Freq());

    HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

    rb_init(&buffer, MAX_SIZE_RB);

    Usart_DMA_Init();

    if (HAL_UART_Receive_DMA(&bboard_uart1_handle, &rxByte, 1) != HAL_OK)
    {
        bboard_usart1_printf("\nCannot receive DMA\n");
        while(1);
    }

    HAL_Delay(2000);
    I2C_init();
    //CM32VR60_init(&i2c_handle);
    CM32VR60_initialization(&i2c_handle);
    GPIO_init();

    int8_t revBuffer[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    uint8_t revLength = 0;
    operationFinished = 0;

    while(1)
    {
#if defined(DEBUG_MODE)
        cmdReceived = 0;
        bboard_led_red_on();
        while (cmdReceived == 0 && operationFinished == 0);

        bboard_led_red_off();

        if (memcmp(rxBuffer, "receive", 8) == 0 || operationFinished == 1)
        {
            int8_t status = CM32VR60_receiveI2C(&i2c_handle,
                    revBuffer, revLength);

            print("Return code: %d\n", status);

            if (status >= 0)
            {
                print("Data:");
                for (uint8_t i = 1; i < revLength; i++)
                    print(" 0x%02X", revBuffer[i]);
                print("\n");
            }

            operationFinished = 0;
        }
        else if (memcmp(rxBuffer, "11", 3) == 0)
        {
            //print("\nReport timestamp:\n");
            CM32VR60_reportTime(&i2c_handle);
            revLength = 6;
        }
        else if (memcmp(rxBuffer, "1", 2) == 0)
        {
            CM32VR60_initialization(&i2c_handle);
            revLength = 1;
        }
        else if (memcmp(rxBuffer, "2", 2) == 0)
        {
            CM32VR60_loadCommandModel(&i2c_handle);
            revLength = 1;
        }
        else if (memcmp(rxBuffer, "8", 2) == 0)
        {
            CM32VR60_startRecognition(&i2c_handle);
            revLength = 4;
        }
        else if (memcmp(rxBuffer, "4", 2) == 0)
        {
            CM32VR60_resetCY(&i2c_handle);
            revLength = 1;
        }
        else if (memcmp(rxBuffer, "5", 2) == 0)
        {
            CM32VR60_resetModel(&i2c_handle);
            revLength = 1;
        }
        else
        {
            bboard_usart1_printf("Wrong command\n");
        }
#else
        //while (rb_get_size(&buffer) == 0 && operationFinished == 0);

        if (operationFinished == 1)
        {
            operationFinished = 0;
        }

        if (rb_get_size(&buffer) > 0)
        {
            uint8_t data[1];
            rb_get_data(&buffer, data, 1);

            if (data[0] == 0xFF) loadModel();
        }

#endif
    }
}

uint32_t ArrToLong(uint8_t *arr)
{
    uint32_t num = 0;

    num |= arr[3] << 24;
    num |= arr[2] << 16;
    num |= arr[1] << 8;
    num |= arr[0];

    return num;
}

void loadModel()
{
    uint8_t sizeArr[4];
    while (rb_get_size(&buffer) < 4);

    rb_get_data(&buffer, sizeArr, 4);

    uint32_t size = ArrToLong(sizeArr);
    uint16_t *cmd_model_length = sizePtr();
    *cmd_model_length = size;
    uint8_t *cmd_model = cmdModelPtr();
    uint32_t index = 0;

    uint8_t data[1];
    while (size)
    {
        if (rb_get_data(&buffer, data, 1) == 1)
        {
            size--;
            cmd_model[index] = data[0];
            index++;
        }
    }

    CM32VR60_loadCommandModel(&i2c_handle);
}

void GPIO_init()
{
    GPIO_InitTypeDef gpio_init_s;

    __GPIOC_CLK_ENABLE();

    gpio_init_s.Mode = GPIO_MODE_IT_RISING;
    gpio_init_s.Pull = GPIO_PULLDOWN;
    gpio_init_s.Speed = GPIO_SPEED_HIGH;
    gpio_init_s.Pin = GPIO_PIN_13;

    HAL_GPIO_Init(GPIOC, &gpio_init_s);

    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void I2C_init()
{
    GPIO_InitTypeDef gpio_init_s;


    /* Enable GPIO clocks */
    __GPIOB_CLK_ENABLE();

    /* Configure GPIOs */
    /* SDA, SCL */
    gpio_init_s.Mode = GPIO_MODE_AF_OD;
    gpio_init_s.Pull = GPIO_NOPULL;
    gpio_init_s.Speed = GPIO_SPEED_HIGH;
    gpio_init_s.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    HAL_GPIO_Init(GPIOB, &gpio_init_s);

    __I2C1_CLK_ENABLE();

    i2c_handle.Instance             = I2C1;

    i2c_handle.Init.ClockSpeed      = 100000; /* Hz */
    i2c_handle.Init.DutyCycle       = I2C_DUTYCYCLE_2;
    i2c_handle.Init.OwnAddress1     = 0x1A;
    i2c_handle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
    i2c_handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE; /* Don't care */
    i2c_handle.Init.OwnAddress2     = 0xFF; /* Don't care */
    i2c_handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE; /* Don't care */
    i2c_handle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE; /* Don't care */

    if (HAL_I2C_Init(&i2c_handle) != HAL_OK)
    {
        print("Error when init I2C.\n");
        while(1);
    }
}

void Usart_DMA_Init()
{
    /* Configure DMA */
    __DMA1_CLK_ENABLE();

    dma_rx_params.Instance = DMA1_Channel5;
    dma_rx_params.Init.Direction = DMA_PERIPH_TO_MEMORY;
    dma_rx_params.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    dma_rx_params.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    dma_rx_params.Init.MemInc = DMA_MINC_ENABLE;
    dma_rx_params.Init.PeriphInc = DMA_PINC_DISABLE;
    dma_rx_params.Init.Mode = DMA_CIRCULAR;
    dma_rx_params.Init.Priority = DMA_PRIORITY_HIGH;

    if (HAL_DMA_Init(&dma_rx_params) != HAL_OK)
    {
        bboard_usart1_printf("\nCannot init DMA\n");
        while(1);
    }

    __HAL_LINKDMA(&bboard_uart1_handle, hdmarx, dma_rx_params);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    operationFinished = 1;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        __HAL_UART_FLUSH_DRREGISTER(huart);


#if defined(DEBUG_MODE)
        bboard_usart1_printf("%c", rxByte);

        /* Backspace or del */
        if (rxByte == 8 || rxByte == 127)
        {
            bboard_usart1_printf(" \b");
            rxIndex--;
            if (rxIndex < 0) rxIndex = 0;
        }
        /* Enter */
        else if (rxByte == '\n' || rxByte == '\r')
        {
            rxBuffer[rxIndex] = 0;
            cmdReceived = 1;
            rxIndex = 0;
            bboard_usart1_printf("\n");
        }

        /* Normal character */
        else
        {
            rxBuffer[rxIndex] = rxByte;
            rxIndex = (rxIndex + 1) % MAX_RX_BUFFER;
        }
#else
        /* Add data to buffer */
        rb_add_data(&buffer, &rxByte, 1);
#endif
    }

}


void SystemClock_Config()
{
    RCC_OscInitTypeDef osc_params;
    RCC_ClkInitTypeDef clk_params;

    HAL_RCC_DeInit();

    osc_params.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    osc_params.HSEState = RCC_HSE_ON;
    osc_params.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    osc_params.PLL.PLLMUL = RCC_PLL_MUL9;
    osc_params.PLL.PLLState = RCC_PLL_ON;
    osc_params.PLL.PLLSource = RCC_PLLSOURCE_HSE;

    if (HAL_RCC_OscConfig(&osc_params) != HAL_OK)
    {
        //error
        bboard_led_red_off();
        while(1);
    }

    clk_params.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK
                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    clk_params.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    clk_params.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clk_params.APB1CLKDivider = RCC_HCLK_DIV2;
    clk_params.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&clk_params, FLASH_LATENCY_2) != HAL_OK)
    {
        //error
        bboard_led_green_off();
        while (1);
    }

    SystemCoreClockUpdate();
}

void print(const char *format, ...)
{
    uint8_t buffer[256];
    va_list args;

    va_start(args, format);
    vsnprintf((char *)buffer, 256, format, args);
    va_end(args);

    /* Print buffer to USART1 */
    HAL_UART_Transmit(&bboard_uart1_handle, buffer, strlen((char *)buffer),
            HAL_MAX_DELAY);
}

void DMA1_Channel5_IRQHandler()
{
    HAL_DMA_IRQHandler(&dma_rx_params);
}

void EXTI15_10_IRQHandler()
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}
