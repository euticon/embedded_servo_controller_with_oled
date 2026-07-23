/*
 * gpio.h
 *
 *  Created on: 08-Jul-2026
 *      Author: adity
 */

#ifndef DEVICE_DRIVERS_GPIO_H_
#define DEVICE_DRIVERS_GPIO_H_

#include "device_headers/stm32f446xx.h"

#define GPIO_PIN_0   0U
#define GPIO_PIN_1   1U
#define GPIO_PIN_2   2U
#define GPIO_PIN_3   3U
#define GPIO_PIN_4   4U
#define GPIO_PIN_5   5U
#define GPIO_PIN_6   6U
#define GPIO_PIN_7   7U
#define GPIO_PIN_8   8U
#define GPIO_PIN_9   9U
#define GPIO_PIN_10  10U
#define GPIO_PIN_11  11U
#define GPIO_PIN_12  12U
#define GPIO_PIN_13  13U
#define GPIO_PIN_14  14U
#define GPIO_PIN_15  15U

#define GPIO_HIGH 1U
#define GPIO_LOW  0U

typedef enum{
	GPIO_MODE_INPUT=0U,
	GPIO_MODE_OUTPUT,
	GPIO_MODE_ALTERNATE,
	GPIO_MODE_ANALOG
}GPIO_Mode_t;

void GPIO_Init(GPIO_TypeDef * port,
		uint8_t pin,
		GPIO_Mode_t mode,
		uint8_t outputType,
		uint8_t outputSpeed,
		uint8_t pullUpDown);

void GPIO_Write(GPIO_TypeDef * port,
		uint8_t pin,
		uint8_t value);

int GPIO_Read(GPIO_TypeDef * port,
		uint8_t pin);

void SelectAltFunction(GPIO_TypeDef * port,
		uint8_t pin, uint8_t alt_func);



#endif /* DEVICE_DRIVERS_GPIO_H_ */
