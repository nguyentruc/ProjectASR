/*
 * model.h
 *
 *  Created on: Apr 22, 2016
 *      Author: dangnhat
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <stdint.h>

uint32_t CY_model_length;
uint8_t CY_model[22032];

uint32_t cmd_model_length;
uint8_t cmd_model[40000];

uint32_t trigger_model_length;
uint8_t trigger_model[2000];

#endif /* MODEL_H_ */
