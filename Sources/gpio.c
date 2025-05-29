/*
 * gpio.c
 *
 *  Created on: Mar 11, 2025
 *      Author: Diogo R Roessler
 */

#include "gpio.h"

#ifdef USE_WITHOUT_HAL_ST
#include "serialize.h"
#endif

#ifdef USE_HAL_ST
#include <stm32f1xx.h>
#endif

#include <stdint.h>

/**
 * @brief Private Delay for GPIO only
 * @param Is long for a better performance is a milliseconds
 * @retval None
 */
void delay_ms(uint32_t ms)
{
	uint32_t i, j;
	for (i = 0; i < 650000 /1000; i++)
	{
		for (j = 0; j < ms; j++)
		{
			asm("nop");
		}
	}
}

#ifdef USE_HAL_ST
/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void GPIO_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOB->CRL &= ~GPIO_CRL_CNF5;
	GPIOB->CRL |= (GPIO_CRL_MODE5_0 | GPIO_CRL_MODE5_1);
	GPIOB->ODR |= GPIO_ODR_ODR5;
}

/**
  * @brief GPIO Toggle Blink Function
  * @param None
  * @retval None
  */
void GPIO_ToggleBlink(void)
{
	GPIOB->ODR ^= GPIO_ODR_ODR5;
	HAL_Delay(1000);
	GPIOB->ODR &= GPIO_ODR_ODR5;
	HAL_Delay(1000);
}

/**
  * @brief Only GPIO Tester Component Worker Status Function
  * @param None
  * @retval None
  */
void GPIO_TesterComponentWorker(uint32_t GPIO_Pin)
{
	GPIOB->ODR ^= GPIO_Pin;
}

/**
  * @brief Only GPIO Tester Component Failure Function
  * @param None
  * @retval None
  */
void GPIO_TesterComponentFailure(uint32_t GPIO_Pin)
{
	GPIOB->ODR &= GPIO_Pin;
}
#endif // USE_HAL_ST

#ifdef USE_WITHOUT_HAL_ST
/**
  * @brief Custom GPIO Initialization Function
  * @param None
  * @retval None
  */
void GPIO_CustomInit(void)
{
	CUSTOM_RCC_APB2ENR |= CUSTOM_RCC_APB2ENR_IOPAEN;
	GPIOA_CRL &= ~CUSTOM_GPIO_CRL_CNF5;
	GPIOA_CRL |= (CUSTOM_GPIO_CRL_MODE5_0 | CUSTOM_GPIO_CRL_MODE5_1);
	GPIOA_ODR |= CUSTOM_GPIO_ODR_ODR5;
}

/**
  * @brief Custom GPIO Toggle Blink Function
  * @param None
  * @retval None
  */
void GPIO_CustomToggleBlink(void)
{
	GPIOA_ODR ^= CUSTOM_GPIO_ODR_ODR5;
	delay_ms(1000);
	GPIOA_ODR &= CUSTOM_GPIO_ODR_ODR5;
	delay_ms(1000);
}

/**
  * @brief Use within SPI for tester led if work
  * @param None
  * @retval None
  */
char GPIO_SPI_CustomOpenLedWorker(void)
{
	GPIOA_ODR ^= CUSTOM_GPIO_ODR_ODR5;
	return 0;
}

/**
  * @brief Use within SPI for tester led if fail
  * @param None
  * @retval None
  */
char GPIO_SPI_CustomOpenLedFailure(void)
{
	GPIOA_ODR &= CUSTOM_GPIO_ODR_ODR5;
	return 0;
}

#endif // USE_WITHOUT_HAL_ST
