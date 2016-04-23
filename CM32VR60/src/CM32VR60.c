/*
 * CM32VR60.c
 *
 *  Created on: Apr 23, 2016
 *      Author: Trung Truc
 */

#include "model.h"
#include "stm32f1xx_hal.h"
#include "CM32VR60.h"

extern void print(const char *format, ...);

void CM32VR60_initialization(I2C_HandleTypeDef *CM32VR60_i2c_handle)
{
    uint8_t cmd[1] = {cmd_initialization};
    HAL_I2C_Master_Transmit(CM32VR60_i2c_handle, IC_ADDR << 1, cmd, 1, 3000);
}

void CM32VR60_loadCommandModel(I2C_HandleTypeDef *CM32VR60_i2c_handle)
{
    uint8_t cmd[1] = {cmd_load_command};
    HAL_I2C_Master_Transmit(CM32VR60_i2c_handle, IC_ADDR << 1, cmd, 1, 3000);
}

void CM32VR60_loadTriggerModel(I2C_HandleTypeDef *CM32VR60_i2c_handle)
{
    uint8_t cmd[1] = {cmd_load_trigger};
    HAL_I2C_Master_Transmit(CM32VR60_i2c_handle, IC_ADDR << 1, cmd, 1, 3000);
}

void CM32VR60_reportTime(I2C_HandleTypeDef *CM32VR60_i2c_handle)
{
    uint8_t cmd[1] = {cmd_report_timestamp};
    HAL_I2C_Master_Transmit(CM32VR60_i2c_handle, IC_ADDR << 1, cmd, 1, 3000);
}

int8_t CM32VR60_receiveI2C(I2C_HandleTypeDef *CM32VR60_i2c_handle,
        int8_t *revBuffer, uint8_t revLength)
{
    HAL_I2C_Master_Receive(CM32VR60_i2c_handle, IC_ADDR << 1, (uint8_t *)revBuffer, 1, 3000);

    if (revBuffer[0] >= 0)
    {
        HAL_I2C_Master_Receive(CM32VR60_i2c_handle, IC_ADDR << 1, (uint8_t *)revBuffer,
                revLength, 3000);
    }

    return revBuffer[0];
}

void CM32VR60_init(I2C_HandleTypeDef *CM32VR60_i2c_handle)
{
    uint8_t cmd[1];

    print("\nResetting CY model...\n");
    cmd[0] = cmd_reset_CY;
    HAL_I2C_Master_Transmit(CM32VR60_i2c_handle, IC_ADDR << 1, cmd, 1, 3000);

    print("\nResetting command model...\n");
    cmd[0] = cmd_reset_cmd;
    HAL_I2C_Master_Transmit(CM32VR60_i2c_handle, IC_ADDR << 1, cmd, 1, 3000);

    print("\nResetting trigger model...\n");
    cmd[0] = cmd_reset_trigger;
    HAL_I2C_Master_Transmit(CM32VR60_i2c_handle, IC_ADDR << 1, cmd, 1, 3000);
}
