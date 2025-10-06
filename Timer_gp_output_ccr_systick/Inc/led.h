/*
 * lcd.h
 *
 *  Created on: Sep 16, 2025
 *      Author: vishal
 */

#ifndef LED_H_
#define LED_H_

#include "stm32f407xx.h"

#define BV(n) (1<<(n))

#define GPIOD_CLK_EN 3
#define LED_GPIO GPIOD

void LED_INIT(uint8_t pin);
void LED_ON(uint8_t pin);
void LED_OFF(uint8_t pin);


#endif /* LED_H_ */
