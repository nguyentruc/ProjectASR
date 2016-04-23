/*
 * Copyright (C) 2015 Ho Chi Minh city University of Technology (HCMUT)
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License.
 */

/**
 * @file        bboard_buttons.h
 * @brief       This is the header of BBoard's Buttons library.
 *******************************************************************************
 *          reset           pressed                             release
 * button ---- i i i i i i i i a a a a a a a a a a a a a a a a a i i i i i i ---
 *                          time_out > 0 ------------- = 0
 *          nothing_new     (set time out).            long_key nothing_new
 *------------------------------------------------------------------------------
 *          reset           pressed                 release
 * button ---- i i i i i i i i a a a a a a a a a a a i i i i i i i i i i i i ---
 *                          time_out > 0 ---------- >0
 *          nothing_new     (set time out).         new_key     nothing_new
 *
 * *****************************************************************************
 *
 * - assign bboard_btn_processing_miscTIM_isr to MiscTIM ISR before calling any 
 * functions.
 *
 * @author      Nhat Pham <phamhuudangnhat@gmail.com>
 */

#ifndef BBOARD_BUTTONS_H_
#define BBOARD_BUTTONS_H_

#include <stdint.h>
#include <stdbool.h>

enum bboard_buttons_e {
    BTN0 = 0,
    BTN1,
};

enum retval_e {
    NO_NEW_KEY = 0,
    NEW_KEY,
    NEW_LONG_KEY,
};

/**
 * @brief   Init BBoard's button.
 *
 * @param[in]   button, btn0 or btn1.
 */
void bboard_btn_init(uint8_t button);

/**
 * @brief   Retrieve a button's status.
 *
 * @param[in]   button, btn0 or btn1.
 *
 * @return      no_new_key, new_key or new_long_key
 */
uint8_t bboard_btn_get_key(uint8_t button);

/**
 * @brief   Check whether a button is still being pressed.
 *
 * @param[in]   button, btn0 or btn1.
 *
 * @return      true if the button is still being pressed.
 */
bool bboard_btn_is_still_long_press(uint8_t button);

/**
 * @brief   Buttons processing function. Should be placed in ISR of a timer with
 *          time-base of 1ms.
 */
void bboard_btn_processing_miscTIM_isr(void);

#endif /* __BBOARD_SYSTEM_H */
