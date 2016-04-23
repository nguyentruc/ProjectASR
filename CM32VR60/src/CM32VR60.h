/*
 * CM32VR60.h
 *
 *  Created on: Apr 23, 2016
 *      Author: dangnhat
 */

#ifndef CM32VR60_H_
#define CM32VR60_H_

#define IC_ADDR 0x50

const enum command_list
{
    cmd_initialization = 0x01,
    cmd_load_command = 0x11,
    cmd_load_trigger = 0x12,
    cmd_reset_CY = 0x20,
    cmd_reset_cmd = 0x21,
    cmd_reset_trigger = 0x22,
    cmd_voicetag_training = 0x31,
    cmd_start_recognition = 0x02,
    cmd_stop_operation = 0x03,
    cmd_playback = 0x09,
    cmd_report_timestamp = 0x05,
    cmd_enter_sleep = 0x0F
} CM32VR60_command;

/* Function prototype */
void CM32VR60_initialization(I2C_HandleTypeDef *CM32VR60_i2c_handle);

void CM32VR60_loadCommandModel(I2C_HandleTypeDef *CM32VR60_i2c_handle);

void CM32VR60_loadTriggerModel(I2C_HandleTypeDef *CM32VR60_i2c_handle);

void CM32VR60_reportTime(I2C_HandleTypeDef *CM32VR60_i2c_handle);

int8_t CM32VR60_receiveI2C(I2C_HandleTypeDef *CM32VR60_i2c_handle,
        int8_t *revBuffer, uint8_t revLength);

void CM32VR60_init(I2C_HandleTypeDef *CM32VR60_i2c_handle);

#endif /* CM32VR60_H_ */
