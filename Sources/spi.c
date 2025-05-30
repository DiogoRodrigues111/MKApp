/*
 * spi.c
 *
 *  Created on: Mar 12, 2025
 *      Author: Diogo R Roessler
 */

#include "VERSION.h"
#include "spi.h"

#ifdef USE_WITHOUT_HAL_ST
#include "serialize.h"
#include "gpio.h"
#endif

#ifdef USE_WITHOUT_HAL_ST

/**
  * @brief SPI1 Initialize
  * @param None
  * @retval None
  */
void SPI1_Init(void)
{
	/* Clock for SPI1, and GPIOA */
	CUSTOM_RCC_APB2ENR |= CUSTOM_RCC_APB2ENR_SPI1EN | CUSTOM_RCC_APB2ENR_IOPAEN;

	/* NSS (Chip Select): PA4 (opcional, dependendo da configuração) */
	GPIOA_CRL &= ~CUSTOM_GPIO_CRL_CNF4;
	GPIOA_CRL |= (CUSTOM_GPIO_CRL_MODE5_0 | CUSTOM_GPIO_CRL_MODE5_1);
	GPIOA_ODR |= CUSTOM_GPIO_ODR_ODR4;

	/* SCK (Serial Clock): PA5 */
	GPIOA_CRL &= ~CUSTOM_GPIO_CRL_CNF5;
	GPIOA_CRL |= (CUSTOM_GPIO_CRL_MODE5_0 | CUSTOM_GPIO_CRL_MODE5_1);
	GPIOA_ODR |= CUSTOM_GPIO_ODR_ODR5;

	/* MISO (Master In Slave Out): PA6 */
	GPIOA_CRL &= ~CUSTOM_GPIO_CRL_CNF6;
	GPIOA_CRL |= (CUSTOM_GPIO_CRL_MODE5_0 | CUSTOM_GPIO_CRL_MODE5_1);
	GPIOA_ODR |= CUSTOM_GPIO_ODR_ODR6;

	/* MOSI (Master Out Slave In): PA7 */
	GPIOA_CRL &= ~CUSTOM_GPIO_CRL_CNF7;
	GPIOA_CRL |= (CUSTOM_GPIO_CRL_MODE5_0 | CUSTOM_GPIO_CRL_MODE5_1);
	GPIOA_ODR |= CUSTOM_GPIO_ODR_ODR7;
}

/**
  * @brief SPI1 Send Command to next
  * @param None
  * @retval None
  */
void SPI1_SendCmd(uint8_t* tx)
{
	while (!(SPI_SR & SPI_SR_TXE)) ;

	SPI_DR |= *tx;

	//while (SPI_SR & SPI_BSY) ;
}

/**
  * @brief SPI1 Receive Command from another
  * @param None
  * @retval None
  */
void SPI1_ReceiveCmd(uint8_t* rx)
{
	//while (!(SPI_SR & SPI_SR_RXNE)) ;

	*rx = (uint8_t)(SPI_DR);

	if (*rx & 0xAA) {
		GPIO_SPI_CustomOpenLedWorker();
	}
	else {
		GPIO_SPI_CustomOpenLedFailure();
	}

	//while (SPI_SR & SPI_BSY) ;
}

/**
  * @brief SPI1 Send Command Test
  * @param None
  * @retval None
  */
void SPI1_SendCmd_Tester(void)
{
	//SPI1_SendCmd(tx);
}

/**
  * @brief SPI1 Receive Command Test
  * @param None
  * @retval None
  */
void SPI1_ReceiveCmd_Tester(void)
{
	//SPI1_ReceiveCmd(tx);
}

#endif // USE_WITHOUT_HAL_ST
