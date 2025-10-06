/*
 * led.c
 *
 *  Created on: Apr 5, 2025
 *      Author: admin
 */

#include "led.h"

void LedInit(uint32_t pin) {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER |= BV(pin*2);
	GPIOD->MODER &= ~BV(pin*2 + 1);
	GPIOD->PUPDR &= ~(BV(pin*2) | BV(pin*2 + 1));
	GPIOD->OSPEEDR &= ~(BV(pin*2) | BV(pin*2 + 1));
	GPIOD->OTYPER &= ~BV(pin);
}

void LedOn(uint32_t pin) {
	GPIOD->ODR|= BV(pin);
}

void LedOff(uint32_t pin) {
	GPIOD->ODR |= BV(pin);
}

void LedToggle(uint32_t pin) {
	GPIOD->ODR ^= BV(pin);
}
