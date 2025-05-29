/*
 * gpio.h
 *
 *  Created on: Mar 11, 2025
 *      Author: Diogo R Roessler
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include <stdint.h>
#include "VERSION.h"

#ifdef USE_HAL_ST

void GPIO_Init(void);
void GPIO_ToggleBlink(void);


/* Tester Component */

void GPIO_TesterComponentWorker(uint32_t GPIO_Pin);
void GPIO_TesterComponentFailure(uint32_t GPIO_Pin);

#endif

#ifdef USE_WITHOUT_HAL_ST

/* PUBLIC CUSTOMS */

void GPIO_CustomInit(void);
void GPIO_CustomToggleBlink(void);

// WITHIN SPI

char GPIO_SPI_CustomOpenLedWorker(void);
char GPIO_SPI_CustomOpenLedFailure(void);

#endif

// PRIVATE:

void delay_ms(uint32_t ms);

#endif /* INC_GPIO_H_ */
