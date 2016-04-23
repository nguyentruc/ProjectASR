/*
 * Copyright (C) 2015 Ho Chi Minh city University of Technology (HCMUT)
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License.
 */

/**
 * @file        bboard_buttons.c
 * @brief       This is the implementation of BBoard's Buttons library.
 *
 * @author      Nhat Pham <phamhuudangnhat@gmail.com>
 */

#include "stm32f1xx_hal.h"
#include "bboard_buttons.h"

/* conf interface (compile-time) */
#define numOfBtns 2

enum btn_active_val_e {
    BTN0_ACT = 0,
    BTN1_ACT = 0,
};

#define btn_samplingTimeCycle 10 /* miscTIM_period */
#define btn_longPressedTime 100 /* btn_samplingTimeCycle */

GPIO_TypeDef *btn_GPIO_ports[numOfBtns] = {GPIOB, GPIOA};
const uint32_t btn_GPIO_pins[numOfBtns] = {GPIO_PIN_2, GPIO_PIN_8};

#define BBOARD_BTN0_CLOCK_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE
#define BBOARD_BTN1_CLOCK_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE

/* end conf interface */

/* private vars */
uint8_t keyRead_1 [numOfBtns] = {!BTN0_ACT, !BTN1_ACT};
uint8_t keyRead_2 [numOfBtns] = {!BTN0_ACT, !BTN1_ACT};
uint8_t keyRead_3 [numOfBtns] = {!BTN0_ACT, !BTN1_ACT};

uint8_t keyOldState [numOfBtns] = {!BTN0_ACT, !BTN1_ACT};

bool isNewKeyPressed [numOfBtns] = {false, false};
bool isLongTimePressed [numOfBtns] = {false, false};
uint16_t longTimePressed_count [numOfBtns] = {0, 0};

uint8_t timeCycle_count = 0;

/* prototypes */
void usrBtn_0_processing (void);
void usrBtn_1_processing (void);

void (*btn_processingFunctions_p [numOfBtns]) (void) = {
    usrBtn_0_processing, 
    usrBtn_1_processing
};

/* private vars */

/*----------------------------------------------------------------------------*/
void bboard_btn_init(uint8_t button)
{   
    if (button == BTN0) {
        BBOARD_BTN0_CLOCK_ENABLE();
    }
    else {
        BBOARD_BTN1_CLOCK_ENABLE();
    }
    
    /* Configure IOs in output push- pull mode to drive external LEDs */
    GPIO_InitTypeDef gpio_init_s;
    
    gpio_init_s.Mode = GPIO_MODE_INPUT;
    gpio_init_s.Pull = GPIO_NOPULL;
    gpio_init_s.Speed = GPIO_SPEED_LOW;
    gpio_init_s.Pin = btn_GPIO_pins[button];
    HAL_GPIO_Init(btn_GPIO_ports[button], &gpio_init_s);
}

/*----------------------------------------------------------------------------*/
uint8_t bboard_btn_get_key(uint8_t button)
{
    if (isNewKeyPressed [button] == true){
        isNewKeyPressed [button] = false;
        return NEW_KEY;
    }
    
    if (isLongTimePressed [button] == true){
        return NEW_LONG_KEY;
    }

    return NO_NEW_KEY;
}

/*----------------------------------------------------------------------------*/
bool bboard_btn_is_still_long_press(uint8_t button)
{
    return isLongTimePressed[button];
}

/*----------------------------------------------------------------------------*/
void bboard_btn_processing_miscTIM_isr (void){
    timeCycle_count = (timeCycle_count + 1) % btn_samplingTimeCycle;

    if (timeCycle_count == (btn_samplingTimeCycle - 1)){
        /* sampling and processing buttons */
        uint8_t a_count;
        for (a_count = 0; a_count < numOfBtns; a_count++){
            if (btn_processingFunctions_p[a_count] != NULL)
                btn_processingFunctions_p[a_count] ();
        }
    }
}

/*----------------------------------------------------------------------------*/
void usrBtn_0_processing (void){
    /* sampling */
    keyRead_3 [BTN0] = keyRead_2 [BTN0];
    keyRead_2 [BTN0] = keyRead_1 [BTN0];
    keyRead_1 [BTN0] = HAL_GPIO_ReadPin(btn_GPIO_ports[BTN0], btn_GPIO_pins[BTN0]);

    /* update longTimePressed_count value */
    if (longTimePressed_count [BTN0] != 0){

        longTimePressed_count [BTN0] --;

        if (longTimePressed_count [BTN0] == 0) // time out, long_key_pressed.
            isLongTimePressed [BTN0] = true;
    }

    /* processing */
    if ( (keyRead_1[BTN0] == keyRead_2[BTN0]) && (keyRead_2[BTN0] == keyRead_3[BTN0]) ){ /* new stable state */

        if (keyRead_1[BTN0] != keyOldState[BTN0]){ /* change state */

            if (keyRead_1[BTN0] == BTN0_ACT){ /* change from inactive->active*/
                keyOldState[BTN0] = keyRead_1[BTN0];

                longTimePressed_count [BTN0] = btn_longPressedTime; //set time out value
            }

            if (keyRead_1[BTN0] == !BTN0_ACT){ /* change from active->inactive*/
                keyOldState[BTN0] = keyRead_1[BTN0];

                if (longTimePressed_count [BTN0] > 0) // not time out yet, new key.
                    isNewKeyPressed[BTN0] = true;

                else // long time pressed key end.
                    isLongTimePressed[BTN0] = false;

                longTimePressed_count [BTN0] = 0;
            }

        }/* end if */

    }/* end if */
}

void usrBtn_1_processing (void){
    /* sampling */
    keyRead_3 [BTN1] = keyRead_2 [BTN1];
    keyRead_2 [BTN1] = keyRead_1 [BTN1];
    keyRead_1 [BTN1] = HAL_GPIO_ReadPin(btn_GPIO_ports[BTN1], btn_GPIO_pins[BTN1]);

    /* update longTimePressed_count value */
    if (longTimePressed_count [BTN1] != 0){

        longTimePressed_count [BTN1] --;

        if (longTimePressed_count [BTN1] == 0) // time out, long_key_pressed.
            isLongTimePressed [BTN1] = true;
    }

    /* processing */
    if ( (keyRead_1[BTN1] == keyRead_2[BTN1]) && (keyRead_2[BTN1] == keyRead_3[BTN1]) ){ /* new stable state */

        if (keyRead_1[BTN1] != keyOldState[BTN1]){ /* change state */

            if (keyRead_1[BTN1] == BTN1_ACT){ /* change from inactive->active*/
                keyOldState[BTN1] = keyRead_1[BTN1];

                longTimePressed_count [BTN1] = btn_longPressedTime; //set time out value
            }

            if (keyRead_1[BTN1] == !BTN1_ACT){ /* change from active->inactive*/
                keyOldState[BTN1] = keyRead_1[BTN1];

                if (longTimePressed_count [BTN1] > 0) // not time out yet, new key.
                    isNewKeyPressed[BTN1] = true;

                else // long time pressed key end.
                    isLongTimePressed[BTN1] = false;

                longTimePressed_count [BTN1] = 0;
            }

        }/* end if */

    }/* end if */
}
