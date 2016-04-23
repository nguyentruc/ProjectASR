/*
 * Copyright (C) 2015 Ho Chi Minh city University of Technology (HCMUT)
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License.
 */

/**
 * @file        bboard_leds.c
 * @brief       This is the implementation of BBoard's LEDs library.
 *
 * @author      Nhat Pham <phamhuudangnhat@gmail.com>
 */

#include "bboard_leds.h"

/* Red LED and Green LED */
#define bboard_num_leds 2
enum led_pos_e {
    LED_GREEN_POS = 0,
    LED_RED_POS = 1,
}; 

enum led_active_val_e {
    LED_GREEN_ACT = 0,
    LED_RED_ACT = 0,
    LED_GREEN_INACT = !LED_GREEN_ACT,
    LED_RED_INACT = !LED_RED_ACT,
};
    
#define BBOARD_RED_LED_CLOCK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define BBOARD_GREEN_LED_CLOCK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE

GPIO_TypeDef *led_gpio[bboard_num_leds] = {GPIOC, GPIOC};
const volatile uint32_t led_pin[bboard_num_leds] = {GPIO_PIN_4, GPIO_PIN_9};

/*----------------------------------------------------------------------------*/
void bboard_led_green_init(void)
{
    BBOARD_GREEN_LED_CLOCK_ENABLE();
    
    /* Configure IOs in output push- pull mode to drive external LEDs */
    GPIO_InitTypeDef gpio_init_s;
    
    gpio_init_s.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_s.Pull = GPIO_PULLUP;
    gpio_init_s.Speed = GPIO_SPEED_HIGH;
    gpio_init_s.Pin = led_pin[LED_GREEN_POS];
    HAL_GPIO_Init(led_gpio[LED_GREEN_POS], &gpio_init_s);
    
    bboard_led_green_off();
}

/*----------------------------------------------------------------------------*/
void bboard_led_red_init(void)
{
    BBOARD_RED_LED_CLOCK_ENABLE();
    
    /* Configure IOs in output push- pull mode to drive external LEDs */
    GPIO_InitTypeDef gpio_init_s;
    
    gpio_init_s.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_s.Pull = GPIO_PULLUP;
    gpio_init_s.Speed = GPIO_SPEED_HIGH;
    gpio_init_s.Pin = led_pin[LED_RED_POS];
    HAL_GPIO_Init(led_gpio[LED_RED_POS], &gpio_init_s);
    
    bboard_led_red_off();
}

/*----------------------------------------------------------------------------*/
void bboard_led_green_on(void)
{
    HAL_GPIO_WritePin(led_gpio[LED_GREEN_POS], led_pin[LED_GREEN_POS],
        (GPIO_PinState) LED_GREEN_ACT);
}

/*----------------------------------------------------------------------------*/
void bboard_led_red_on(void)
{
    HAL_GPIO_WritePin(led_gpio[LED_RED_POS], led_pin[LED_RED_POS],
        (GPIO_PinState) LED_RED_ACT);
}

/*----------------------------------------------------------------------------*/
void bboard_led_green_off(void)
{
    HAL_GPIO_WritePin(led_gpio[LED_GREEN_POS], led_pin[LED_GREEN_POS], 
        (GPIO_PinState) LED_GREEN_INACT);
}

/*----------------------------------------------------------------------------*/
void bboard_led_red_off(void)
{
    HAL_GPIO_WritePin(led_gpio[LED_RED_POS], led_pin[LED_RED_POS], 
        (GPIO_PinState) LED_RED_INACT);
}

/*----------------------------------------------------------------------------*/
void bboard_led_green_toggle(void)
{
    HAL_GPIO_TogglePin(led_gpio[LED_GREEN_POS], led_pin[LED_GREEN_POS]);
}

/*----------------------------------------------------------------------------*/
void bboard_led_red_toggle(void)
{
    HAL_GPIO_TogglePin(led_gpio[LED_RED_POS], led_pin[LED_RED_POS]);
}
