/*
 * timers.h
 *
 *  Created on: 10-Jul-2026
 *      Author: adity
 */

#include "device_headers/stm32f446xx.h"
#include <stdint.h>

#ifndef DEVICE_DRIVERS_TIMERS_H_
#define DEVICE_DRIVERS_TIMERS_H_



#define CLK_16MHZ 16000000U


typedef enum{
	stop,
	slow,
	medium,
	fast
}speed_type;

typedef enum{
	CW,
	ACW
}direction_type;

extern speed_type current_speed;
extern direction_type current_direction;

void PWM_Init(TIM_TypeDef *timer);

void ServoMotor_Init(uint16_t period_ms);

void SetServoSpeed_Direction(uint16_t period_ms,speed_type speed,direction_type direction);

#endif /* DEVICE_DRIVERS_TIMERS_H_ */
