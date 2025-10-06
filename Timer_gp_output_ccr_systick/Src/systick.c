/*
 * systick.c
 *
 *  Created on: Sep 30, 2025
 *      Author: vishal
 */
#include"systick.h"

volatile uint32_t xtick=0;

void SysTick_Handler(void)
{
	xtick++;
}

void SystickDelayms(uint32_t ms)
{
	uint32_t counter=xtick;
	uint32_t wait=counter+ms;
	while(xtick<wait);
}


