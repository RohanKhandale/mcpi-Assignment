/*
 * timer.c
 *
 *  Created on: Sep 29, 2025
 *      Author: vishal
 */

#include "Timer.h"

volatile uint32_t flag=0;

void TimerInit(uint32_t ms)
{
	//clk
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
	TIM7->PSC=PR-1;
	uint32_t cnt= (fpclk/1000)*ms/PR;
	TIM7->ARR=cnt-1;
	TIM7->CNT=0;

	TIM7->DIER |= TIM_DIER_UIE;

	NVIC_EnableIRQ(TIM7_IRQn);


	TIM7->CR1 |= TIM_CR1_CEN;
}

void TIM7_IRQHandler(void)
{
	if (TIM7->SR & TIM_SR_UIF)
	{
		flag++;
		TIM7->SR &= ~TIM_SR_UIF;
	}
}

