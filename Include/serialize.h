/*
 * serialize.h
 *
 *  Created on: Mar 11, 2025
 *      Author: Diogo R Roessler
 */

#ifndef INCLUDE_SERIALIZE_H_
#define INCLUDE_SERIALIZE_H_

#include <stdint.h>

#define CUSTOM_RCC_BASE		0x40021000
#define CUSTOM_GPIOA_BASE	0x40010800
#define CUSTOM_GPIOB_BASE	0x40010C00
#define CUSTOM_GPIOC_BASE	0x40011000
#define CUSTOM_SPI1_BASE	0x40013000
#define CUSTOM_USART1_BASE	0x40013800
#define CUSTOM_USART2_BASE	0x40004400
#define CUSTOM_WWDG_BASE	0x40002C00
#define CUSTOM_IWDG_BASE	0x40003000
#define CUSTOM_DAC_BASE		0x40007400
#define CUSTOM_ADC1_BASE	0x40012400
#define CUSTOM_I2C1_BASE	0x40005400
#define CUSTOM_I2C2_BASE	0x40005800
#define CUSTOM_AFIO_BASE	0x40010000
#define CUSTOM_EXTI_BASE	0x40010400

/* USART1EN, SPI1EN, TIM1EN, ADC2EN, ADC1EN, IOPxEN, AFIOEN */
#define CUSTOM_RCC_APB2ENR	(*(volatile uint32_t *)(CUSTOM_RCC_BASE + 0x18))

/* DACEN, PWREN, BKPEN,
 * CAN2EN, CAN1EN,
 * I2C2EN, I2C1EN,
 * UART5EN, UART4EN, USART3EN, USART2EN,
 * SPI3EN, SPI2EN, WWDGEN,
 * TIM7EN, TIM6EN, TIM5EN, TIM4EN, TIM3EN, TIM2EN */
#define CUSTOM_RCC_APB1ENR	(*(volatile uint32_t *)(CUSTOM_RCC_BASE + 0x1C))

#define CUSTOM_RCC_APB2ENR_IOPBEN	(1 << 3)
#define CUSTOM_RCC_APB2ENR_IOPAEN	(1 << 2)
#define CUSTOM_RCC_APB2ENR_AFIOEN	(1 << 0)
#define CUSTOM_RCC_APB2ENR_USART1EN	(1 << 14)
#define CUSTOM_RCC_APB2ENR_SPI1EN	(1 << 12)
#define CUSTOM_RCC_APB2ENR_TIM1EN	(1 << 11)
#define CUSTOM_RCC_APB2ENR_ADC2EN	(1 << 10)
#define CUSTOM_RCC_APB2ENR_ADC1EN	(1 << 9)

/* GPIO Flags */

#define GPIOB_CRL	(*(volatile uint32_t *)(CUSTOM_GPIOB_BASE + 0x00))
#define GPIOB_ODR	(*(volatile uint32_t *)(CUSTOM_GPIOB_BASE + 0x0C))
#define GPIOB_BSRR	(*(volatile uint32_t *)(CUSTOM_GPIOB_BASE + 0x10))
#define GPIOB_BRR	(*(volatile uint32_t *)(CUSTOM_GPIOB_BASE + 0x14))

#define GPIOA_CRL	(*(volatile uint32_t *)(CUSTOM_GPIOA_BASE + 0x00))
#define GPIOA_ODR	(*(volatile uint32_t *)(CUSTOM_GPIOA_BASE + 0x0C))
#define GPIOA_BSRR	(*(volatile uint32_t *)(CUSTOM_GPIOA_BASE + 0x10))
#define GPIOA_BRR	(*(volatile uint32_t *)(CUSTOM_GPIOA_BASE + 0x14))
#define GPIOA_IDR	(*(volatile uint32_t *)(CUSTOM_GPIOA_BASE + 0x08))
#define GPIOA_CRH	(*(volatile uint32_t *)(CUSTOM_GPIOA_BASE + 0x04))

/* CNF and MODE */

#define Analog_mode	0x0
#define Floating_input_RESETSTATE 0x1
#define Input_pull_up_down 0x2
#define __INPUT_MODE_RESERVED__ 0x3

#define General_purpose_output_push_pull 0x0UL
#define General_purpose_output_open_drain 0x1UL
#define Alternate_function_output_push_pull 0x2UL
#define Alternate_function_output_open_drain 0x3UL

#define Input_mode_RESETSTATE	0x0UL
#define Output_mode_10MHz	0x1UL
#define Output_mode_2MHz	0x2UL
#define Output_mode_50MHz	0x3UL

/* SPI */

/**** SPI control register 1 ****/

// (not used in I2S mode
#define SPI_CR1			(*(volatile uint32_t *)(CUSTOM_SPI1_BASE + 0x00))

// Bidirectional data mode enable
/*
 0: 2-line unidirectional data mode selected
 1: 1-line bidirectional data mode selected

 Note: This bit is not used in I2S mode
 */
//1-line bidirectional data mode selected
#define SPI_BIDIMODE_ENABLE		(1 << 15)
// 2-line unidirectional data mode selected
#define SPI_BIDIMODE_DISABLE	(0 << 15)

// Output enable in bidirectional mode

/*
 This bit combined with the BIDImode bit selects the direction of transfer in bidirectional mode
0: Output disabled (receive-only mode)
1: Output enabled (transmit-only mode)
Note: This bit is not used in I2S mode.
In master mode, the MOSI pin is used while the MISO pin is used in slave mode.
 */

#define SPI_BIDIOE_ENABLE		(1 << 14)
#define SPI_BIDIOE_DISABLE		(0 << 14)

// CRC transfer next

/*
 0: Data phase (no CRC phase)
1: Next transfer is CRC (CRC phase)
Note:When the SPI is configured in full duplex or transmitter only modes, CRCNEXT must be
written as soon as the last data is written to the SPI_DR register.
When the SPI is configured in receiver only mode, CRCNEXT must be set after the
second last data reception.
This bit should be kept cleared when the transfers are managed by DMA.
It is not used in I2S mode.
 */

#define SPI_CRCNEXT_ENABLE		(1 << 12)
#define SPI_CRCNEXT_DISABLE		(0 << 12)

// Data frame format

/*
 0: 8-bit data frame format is selected for transmission/reception
1: 16-bit data frame format is selected for transmission/reception
Note: This bit should be written only when SPI is disabled (SPE = ‘0’) for correct operation.
It is not used in I2S mode.
 */

#define SPI_DFF_ENABLE			(1 << 11)
#define SPI_DFF_DISABLE			(0 << 11)

// Receive only

/*
 This bit combined with the BIDImode bit selects the direction of transfer in 2-line
unidirectional mode. This bit is also useful in a multislave system in which this particular
slave is not accessed, the output from the accessed slave is not corrupted.
0: Full duplex (Transmit and receive)
1: Output disabled (Receive-only mode)
Note: This bit is not used in I2S mode
 */

#define SPI_RXONLY_ENABLE		(1 << 10)
#define SPI_RXONLY_DISABLE		(0 << 10)

// SPI enable

/*
 0: Peripheral disabled
 1: Peripheral enabled
Note: This bit is not used in I2S mode.
When disabling the SPI, follow the procedure described in Section 25.3.8 .
 */

#define SPI_SPE_ENABLE			(1 << 6)
#define SPI_SPE_DISABLE			(0 << 6)

// Baud rate control

/*

 000: fPCLK/2
001: fPCLK/4
010: fPCLK/8
011: fPCLK/16
100: fPCLK/32
101: fPCLK/64
110: fPCLK/128
111: fPCLK /256
Note: These bits should not be changed when communication is ongoing.
They are not used in I2S mode.

 */

#define SPI_BR					(1 << 5)

// Master selection

/*
 0: Slave configuration
1: Master configuration
Note: This bit should not be changed when communication is ongoing.
It is not used in I2S mode.
 */

#define SPI_MSTR				(1 << 2)

/*** SPI control register 2 ***/

#define SPI_CR2					(*(volatile uint32_t *)(CUSTOM_SPI1_BASE + 0x04))

// Tx buffer empty interrupt enable

/*
 0: TXE interrupt masked
1: TXE interrupt not masked. Used to generate an interrupt request when the TXE flag is set.
 */

#define SPI_TXEIE_ENABLE		(1 << 7)

// RX buffer not empty interrupt enable

/*
 0: RXNE interrupt masked
1: RXNE interrupt not masked. Used to generate an interrupt request when the RXNE flag is
set.
 */

#define SPI_RXNEIE_ENABLE				(1 << 6)
#define SPI_RXNEIE_DISABLE				(0 << 6)

// Error interrupt enable

/*
 This bit controls the generation of an interrupt when an error condition occurs (CRCERR,
OVR, MODF in SPI mode and UDR, OVR in I2S mode).
0: Error interrupt is masked
1: Error interrupt is enabled
 */

#define SPI_ERRIE_ENABLE				(1 << 5)
#define SPI_ERRIE_DISABLE				(0 << 5)

// Tx buffer DMA enable

/*
 When this bit is set, the DMA request is made whenever the TXE flag is set.
0: Tx buffer DMA disabled
1: Tx buffer DMA enabled
 */

#define SPI_TXDMAEN_ENABLE				(1 << 1)
#define SPI_TXDMAEN_DISABLE				(0 << 1)

// Rx buffer DMA enable

/*
 When this bit is set, the DMA request is made whenever the RXNE flag is set.
0: Rx buffer DMA disabled
1: Rx buffer DMA enabled
 */

#define SPI_RXDMAEN_ENABLE				(1 << 0)
#define SPI_RXDMAEN_DISABLE				(0 << 0)

/*** SPI status register ***/

#define SPI_SR							(*(volatile uint32_t *)(CUSTOM_SPI1_BASE + 0x08))

// Busy flag

/*
 0: SPI (or I2S) not busy
1: SPI (or I2S) is busy in communication or Tx buffer is not empty
This flag is set and cleared by hardware.
Note: BSY flag must be used with caution: refer to Section 25.3.7 and Section 25.3.8.
 */

#define SPI_BSY							(1 << 7)

// Mode fault

/*
 0: No mode fault occurred
1: Mode fault occurred
This flag is set by hardware and reset by a software sequence. Refer to Section 25.4.7:
Error flags for the software sequence.
Note: This bit is not used in I2S mode
 */

#define SPI_SR_MODF						(1 << 5)

// Transmit buffer empty

/*
 0: Tx buffer not empty
1: Tx buffer empty
 */

#define SPI_SR_TXE						(1 << 1)

// Receive buffer not empty

/*
 0: Rx buffer empty
1: Rx buffer not empty
 */

#define SPI_SR_RXNE						(1 << 0)

#define SPI_DR						(*(volatile uint32_t *)(CUSTOM_SPI1_BASE + 0x0C))

/* GPIO Pin */

#define CUSTOM_GPIO_CRL_MODE4_0		(Output_mode_10MHz << (16U)) // (0x1UL = representa SPEED) - (MODE5_0 | MODE5_1) = 0b11 = 50Mhz
#define CUSTOM_GPIO_CRL_MODE4_1		(Output_mode_10MHz << (17U))
#define CUSTOM_GPIO_CRL_CNF4		(Alternate_function_output_open_drain << (18U)) // (0x3UL = MODE_PIN [PushPull, OpenDrain, etc..]) [SEMPRE É MELHOR (22U), pois é menor que (23U)] sempre prefira menor
#define CUSTOM_GPIO_ODR_ODR4		(0x1UL << (4U)) 			// ENABLE

#define CUSTOM_GPIO_CRL_MODE5_0		(Output_mode_10MHz << (20U)) // (0x1UL = representa SPEED) - (MODE5_0 | MODE5_1) = 0b11 = 50Mhz
#define CUSTOM_GPIO_CRL_MODE5_1		(Output_mode_10MHz << (21U)) // (0x1UL << (21)) | (0x2UL << (20U)) //21 (0x1UL = SPEED)
#define CUSTOM_GPIO_CRL_CNF5		(Alternate_function_output_open_drain << (22U)) // (0x3UL = MODE_PIN [PushPull, OpenDrain, etc..]) [SEMPRE É MELHOR (22U), pois é menor que (23U)] sempre prefira menor
#define CUSTOM_GPIO_ODR_ODR5		(0x1UL << (5U)) 			// ENABLE

#define CUSTOM_GPIO_CRL_MODE6_0		(Output_mode_10MHz << (24U)) // (0x1UL = representa SPEED) - (MODE5_0 | MODE5_1) = 0b11 = 50Mhz
#define CUSTOM_GPIO_CRL_MODE6_1		(Output_mode_10MHz << (25U))
#define CUSTOM_GPIO_CRL_CNF6		(Alternate_function_output_open_drain << (26U)) // (0x3UL = MODE_PIN [PushPull, OpenDrain, etc..]) [SEMPRE É MELHOR (22U), pois é menor que (23U)] sempre prefira menor
#define CUSTOM_GPIO_ODR_ODR6		(0x1UL << (6U)) 			// ENABLE

#define CUSTOM_GPIO_CRL_MODE7_0		(Output_mode_10MHz << (28U)) // (0x1UL = representa SPEED) - (MODE5_0 | MODE5_1) = 0b11 = 50Mhz
#define CUSTOM_GPIO_CRL_MODE7_1		(Output_mode_10MHz << (29U))
#define CUSTOM_GPIO_CRL_CNF7		(Alternate_function_output_open_drain << (30U)) // (0x3UL = MODE_PIN [PushPull, OpenDrain, etc..]) [SEMPRE É MELHOR (22U), pois é menor que (23U)] sempre prefira menor
#define CUSTOM_GPIO_ODR_ODR7		(0x1UL << (7U)) 			// ENABLE

#endif /* INCLUDE_SERIALIZE_H_ */
