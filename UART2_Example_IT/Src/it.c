/*
 * it.c
 *
 *  Created on: Nov 25, 2020
 *      Author: Gustavo
 */
#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart2;

void SysTick_Handler(void) {
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void USART2_IRQHandler(void) {
	HAL_UART_IRQHandler(&huart2);
}
