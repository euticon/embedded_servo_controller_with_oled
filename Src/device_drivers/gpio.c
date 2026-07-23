/*
 * gpio.c
 *
 *  Created on: 08-Jul-2026
 *      Author: adity
 */
#include "device_drivers/gpio.h"

void GPIO_Init(GPIO_TypeDef * port,
		uint8_t pin,
		GPIO_Mode_t mode,
		uint8_t outputType,
		uint8_t outputSpeed,
		uint8_t pullUpDown)
{
	port->MODER&=~(3U<<pin*2);
	port->MODER|=(uint32_t)(mode<<(pin*2U));

	port->OTYPER&=~(1U<<pin);
	port->OTYPER|=((uint32_t)(outputType<<pin));

	port->OSPEEDR&=~(3U<<pin*2);
	port->OSPEEDR|=(uint32_t)(outputSpeed<<(pin*2U));

	port->PUPDR&=~(3U<<pin*2);
	port->PUPDR|=(uint32_t)(pullUpDown<<(pin*2U));

}

void GPIO_Write(GPIO_TypeDef * port,
		uint8_t pin,
		uint8_t value)
{
	port->BSRR|=(value)?(1<<pin):(1<<(pin+16));
}

int GPIO_Read(GPIO_TypeDef * port,
		uint8_t pin)
{
	return !((port->IDR)&(1<<pin));
}

void SelectAltFunction(GPIO_TypeDef * port,
		uint8_t pin, uint8_t alt_func)
{
	alt_func&=0xFU;
	if(pin<=7)
	{
		port->AFR[0]&=~(0xFU<<(pin*4));
		port->AFR[0]|=(uint32_t)(alt_func<<(pin*4));
	}
	else
	{
		port->AFR[1]&=~(0xFU<<((pin-8)*4));
		port->AFR[1]|=(uint32_t)(alt_func<<((pin-8)*4));
	}

}

