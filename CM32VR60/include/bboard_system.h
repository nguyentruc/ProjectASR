/*
 * Copyright (C) 2015 Ho Chi Minh city University of Technology (HCMUT)
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License.
 */

/**
 * @file        bboard_system.h
 * @brief       This is the entry point of Bboard library
 *
 * @author      Nhat Pham <phamhuudangnhat@gmail.com>
 */
 
#ifndef __BBOARD_SYSTEM_H
#define __BBOARD_SYSTEM_H

#include "stm32f1xx_hal.h"
#include "bboard_leds.h"
#include "bboard_buttons.h"

/* USART 1 */
extern UART_HandleTypeDef bboard_uart1_handle;

/* Retarget */
#define BBOARD_RETARGET_UART_PTR    bboard_uart1_handle;

/**
 * @brief   Init usart1 in uart mode (8 bit data, 0 parity) with given baudrate.
 *
 * @param[in]   buadrate.
 */
void bboard_usart1_init(uint32_t buadrate);

/**
 * @brief   Printf via USART1. This function will print data to USART1 directly 
 *          rather than depending on library like retarget method. No buffering
 *          was implemented in this function.
 *
 * @param[in]   format, similar to printf's counterpart.
 */
void bboard_usart1_printf(const char *format, ...);

#endif /* __BBOARD_SYSTEM_H */
