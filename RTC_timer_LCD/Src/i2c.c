/*
 * i2c.c
 *
 *  Created on: Mar 31, 2025
 *      Author: admin
 */

#include "i2c.h"

void I2CInit(void) {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER |= BV(2*6+1) | BV(2*9+1);
	GPIOB->MODER &= ~(BV(2*6) | BV(2*9));
	GPIOB->AFR[0] = 4 << (4*6);
	GPIOB->AFR[1] = 4 << (4*1);
	GPIOB->PUPDR &= ~(BV(2*6+1) | BV(2*9+1) | BV(2*6) | BV(2*9));
	GPIOB->OTYPER |= BV(6) | BV(9);

	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

	I2C1->CR1 |= I2C_CR1_SWRST;//Software under Reset
	I2C1->CR1 = 0;//Software not reset
	I2C1->CR2 |= 16 << I2C_CR2_FREQ_Pos; //frequency is 16MHz PCLK1
	I2C1->CCR = 80;//Set CCR to 80 for getting frequency of I2C 100MHz
	I2C1->CCR &= ~I2C_CCR_FS;//Selecting SM mode
	I2C1->TRISE = 17;//Setting Trise to 17 to get trise time for 16MHz
	I2C1->CR1 |= I2C_CR1_ACK;//ack return after a byte recived
	I2C1->CR1 |= I2C_CR1_PE;// peripheral enable
}

void I2CStart(void) {
	I2C1->CR1 |= I2C_CR1_START;//Start I2C
	while(!(I2C1->SR1 & I2C_SR1_SB));//when start bit set, Hardware set SB bit to 1 so wait until it becomes 1
}

void I2CRepeatStart(void) {
	I2CStart();//Repeat star for reading multiple byte data
}

void I2CStop(void) {
	I2C1->CR1 |= I2C_CR1_STOP;//Stop I2C bit
	while(I2C1->SR2 & I2C_SR2_BUSY);//wait until communication is completed
}

void I2CSendSlaveAddr(uint8_t addr) {
	I2C1->DR = addr;
	while(!(I2C1->SR1 & I2C_SR1_ADDR));//wait until address matched
	(void)I2C1->SR1;//to clear addr by software reading SR1 followed by SR2
	(void)I2C1->SR2;
	//I2C1->CR1 &=~(BV(0));
}

void I2CSendData(uint8_t data) {
	while(!(I2C1->SR1 & I2C_SR1_TXE));
	I2C1->DR = data;
    while (!(I2C1->SR1 & I2C_SR1_BTF));
}

uint8_t I2CRecvDataAck(void) {
	I2C1->CR1 |= I2C_CR1_ACK | I2C_CR1_POS;
	while(!(I2C1->SR1 & I2C_SR1_RXNE));
	return I2C1->DR;
}

uint8_t I2CRecvDataNAck(void) {
	I2C1->CR1 &= ~(I2C_CR1_ACK | I2C_CR1_POS);
	while(!(I2C1->SR1 & I2C_SR1_RXNE));
	return I2C1->DR;
}

void I2CWrite(uint8_t addr, uint8_t data) {
	I2CStart();
	I2CSendSlaveAddr(addr);
	I2CSendData(data);
	I2CStop();
}
