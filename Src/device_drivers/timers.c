/*
 * timers.c
 *
 *  Created on: 10-Jul-2026
 *      Author: adity
 */

#include "device_drivers/timers.h"

speed_type current_speed = stop;
direction_type current_direction = CW;

void PWM_Init(TIM_TypeDef *timer)
{
	timer->CR1|=0x80U;
	timer->CCMR1|=0x68U;
	timer->CCER|=0x01U;
	timer->CNT|=0x0U;
	timer->PSC=40U-1U;
	timer->ARR=1000U-1U;
	timer->CCR1=10U-1U;
	timer->EGR|=1U;
	timer->CR1|=0x1U;

}

void ServoMotor_Init(uint16_t period_ms)
{
		TIM2->CR1|=0x80U;
		TIM2->CCMR1|=0x68U;
		TIM2->CCER|=0x01U;
		TIM2->CNT|=0x0U;
		TIM2->PSC=16U-1U;
		TIM2->ARR=(CLK_16MHZ*period_ms)/(16*1000)-1U;
		TIM2->CCR1=10U-1U;
		TIM2->EGR|=1U;
		TIM2->CR1|=0x1U;
}

void SetServoSpeed_Direction(uint16_t period_ms,speed_type speed,direction_type direction)
{
	current_speed = speed;
		current_direction = direction;
	//uint32_t arr=TIM2->ARR;
	if(speed!=0&&speed!=1&&speed!=2&&speed!=3)speed=0;
	if(direction!=0&&direction!=1)direction=0;

	//map(speed,direction): (0,0)-->stopped, (0,1)-->stopped, (1,0)-->slow,CW. (1,1)-->slow,ACW
	//(2,0)-->medium,CW, (2,1)-->medium,ACW, (3,0)-->fast,CW, (3,1)-->fast,ACW

	if(speed==0)TIM2->CCR1=500+1000;
	if(speed==3&&direction==0)TIM2->CCR1=500;
	if(speed==2&&direction==0)TIM2->CCR1=500+500;
	if(speed==1&&direction==0)TIM2->CCR1=500+750;
	if(speed==1&&direction==1)TIM2->CCR1=500+1250;
	if(speed==2&&direction==1)TIM2->CCR1=500+1500;
	if(speed==3&&direction==1)TIM2->CCR1=500+2200;


	//uint32_t pulse_us=500+((uint32_t)servo_angle*2000)/180;

	//TIM2->CCR1=(pulse_us*(arr+1))/(period_ms*1000);
}
