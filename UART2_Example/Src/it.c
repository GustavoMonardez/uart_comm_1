/*
 * it.c
 *
 *  Created on: Nov 25, 2020
 *      Author: Gustavo
 */
#include "stm32f4xx_hal.h"

void SysTick_Handler(void) {
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

