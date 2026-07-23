/*
 * i2c.h
 *
 *  Created on: 19-Jul-2026
 *      Author: adity
 */

#ifndef DEVICE_DRIVERS_I2C_H_
#define DEVICE_DRIVERS_I2C_H_


#include <stdint.h>
#include "device_headers/stm32f446xx.h"

void i2c_init();

uint8_t i2c_check_addr(uint8_t addr);

#endif /* DEVICE_DRIVERS_I2C_H_ */
