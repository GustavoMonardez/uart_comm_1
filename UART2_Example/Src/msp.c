/*
 * msp.c
 *
 *  Created on: Nov 25, 2020
 *      Author: Gustavo
 */

#include "stm32f4xx_hal.h"

/* MSP (Microcontroller Support Package */
void HAL_MspInit(void) {
	/* The following settings depend on the type
	 * of application being developed */

	// 1. Set up the priority grouping of the arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	// 2. Enable the required system exceptions of the arm cortex mx processor
	SCB->SHCSR |= 0x7 << 16; /*usg fault, mem fault and bus fault - Cortex manual */

	// 3. Configure the priority for the system exceptions
	// Note: By default exceptions are the highest priority (0),
	// so this step is optional. Priority range 0-15, 0 is highest.
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}

// Low level peripheral initialization
// Note: If this aren't working as they should, this function
// should be the first place to look at.
void HAL_UART_MspInit(UART_HandleTypeDef *huart) {
	GPIO_InitTypeDef gpio_uart;
	// 1. Enable the clock for USART2 peripheral and GPIOA
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	// 2. Do pin muxing configurations
	// Pin 2, port A (USART2_TX)
	gpio_uart.Pin = GPIO_PIN_2;
	gpio_uart.Mode = GPIO_MODE_AF_PP;
	gpio_uart.Pull = GPIO_PULLUP;
	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	// Pin 3, port A (USART2_RX)
	gpio_uart.Pin = GPIO_PIN_3;
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	// 3. Enable the IRQ and set up the priority (NVIC settings)
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);
}
