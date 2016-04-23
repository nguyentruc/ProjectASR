/*
 * Copyright (C) 2015 Ho Chi Minh city University of Technology (HCMUT)
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License.
 */

/**
 * @file        bboard_leds.h
 * @brief       This is the header of BBoard's LEDs library.
 *
 * @author      Nhat Pham <phamhuudangnhat@gmail.com>
 */
 
#ifndef __BBOARD_LEDS_H
#define __BBOARD_LEDS_H

#include "stm32f1xx_hal.h"

/**
 * @brief   Init BBoard's green LED.
 */
void bboard_led_green_init(void);

/**
 * @brief   Init BBoard's red LED.
 */
void bboard_led_red_init(void);

/**
 * @brief   Turn on BBoard's green LED.
 */
void bboard_led_green_on(void);

/**
 * @brief   Turn on BBoard's red LED.
 */
void bboard_led_red_on(void);

/**
 * @brief   Turn off BBoard's green LED.
 */
void bboard_led_green_off(void);

/**
 * @brief   Turn off BBoard's red LED.
 */
void bboard_led_red_off(void);

/**
 * @brief   Toggle BBoard's green LED.
 */
void bboard_led_green_toggle(void);

/**
 * @brief   Toggle BBoard's red LED.
 */
void bboard_led_red_toggle(void);

#endif /* __BBOARD_LEDS_H */
