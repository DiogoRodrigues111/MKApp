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

/*** USART / UART ***/

/* Begin USART1_SR / USART2_SR */

// Status register
#define USART1_SR					(*(volatile uint32_t *)(CUSTOM_USART1_BASE + 0x00))
#define USART2_SR					(*(volatile uint32_t *)(CUSTOM_USART2_BASE + 0x00))

// CTS flag
/*
 This bit is set by hardware when the CTS input toggles, if the CTSE bit is set. It is cleared by
software (by writing it to 0). An interrupt is generated if CTSIE=1 in the USART_CR3
register.
0: No change occurred on the CTS status line
1: A change occurred on the CTS status line
This bit is not available for UART4 & UART5.
 */
#define USART_CTS_EN				(1 << 9)
#define USART_CTS_NE				(0 << 9)

// LIN break detection flag
/*
 This bit is set by hardware when the LIN break is detected. It is cleared by software (by
writing it to 0). An interrupt is generated if LBDIE = 1 in the USART_CR2 register.
0: LIN Break not detected
1: LIN break detected
Note: An interrupt is generated when LBD=1 if LBDIE=1
 */
#define USART_LBD_EN				(1 << 8)
#define USART_LBD_NE				(0 << 8)

// Transmit data register empty
/*
 This bit is set by hardware when the content of the TDR register has been transferred into
the shift register. An interrupt is generated if the TXEIE bit =1 in the USART_CR1 register. It
is cleared by a write to the USART_DR register.
0: Data is not transferred to the shift register
1: Data is transferred to the shift register)
Note: This bit is used during single buffer transmission.
 */
#define USART_TXE_EN				(1 << 7)
#define USART_TXE_NE				(0 << 7)

// Transmission complete
/*
 This bit is set by hardware if the transmission of a frame containing data is complete and if
TXE is set. An interrupt is generated if TCIE=1 in the USART_CR1 register. It is cleared by a
software sequence (a read from the USART_SR register followed by a write to the
USART_DR register). The TC bit can also be cleared by writing a '0' to it. This clearing
sequence is recommended only for multibuffer communication.
0: Transmission is not complete
1: Transmission is complete
 */
#define USART_TC_EN					(1 << 6)
#define USART_TC_NE					(0 << 6)

// Read data register not empty
/*
 This bit is set by hardware when the content of the RDR shift register has been transferred to
the USART_DR register. An interrupt is generated if RXNEIE=1 in the USART_CR1 register.
It is cleared by a read to the USART_DR register. The RXNE flag can also be cleared by
writing a zero to it. This clearing sequence is recommended only for multibuffer
communication.
0: Data is not received
1: Received data is ready to be read.
 */
#define USART_RXNE_EN				(1 << 5)
#define USART_RXNE_NE				(0 << 5)

// IDLE line detected
/*
 This bit is set by hardware when an Idle Line is detected. An interrupt is generated if the
IDLEIE=1 in the USART_CR1 register. It is cleared by a software sequence (an read to the
USART_SR register followed by a read to the USART_DR register).
0: No Idle Line is detected
1: Idle Line is detected
Note: The IDLE bit will not be set again until the RXNE bit has been set itself (i.e. a new idle
line occurs).
 */
#define USART_IDLE_EN				(1 << 4)
#define USART_IDLE_NE				(0 << 4)

// Overrun error
/*
 This bit is set by hardware when the word currently being received in the shift register is
ready to be transferred into the RDR register while RXNE=1. An interrupt is generated if
RXNEIE=1 in the USART_CR1 register. It is cleared by a software sequence (an read to the
USART_SR register followed by a read to the USART_DR register).
0: No Overrun error
1: Overrun error is detected
Note:When this bit is set, the RDR register content will not be lost but the shift register will be
overwritten. An interrupt is generated on ORE flag in case of Multi Buffer
communication if the EIE bit is set.
 */
#define USART_ORE_EN				(1 << 3)
#define USART_ORE_NE				(0 << 3)

// Noise error flag
/*
 This bit is set by hardware when noise is detected on a received frame. It is cleared by a
software sequence (an read to the USART_SR register followed by a read to the
USART_DR register).
0: No noise is detected
1: Noise is detected
Note:This bit does not generate interrupt as it appears at the same time as the RXNE bit
which itself generates an interrupting interrupt is generated on NE flag in case of Multi
Buffer communication if the EIE bit is set.
 */
#define USART_NE_EN					(1 << 2)
#define USART_NE_NE					(0 << 2)

// Framing error
/*
 This bit is set by hardware when a de-synchronization, excessive noise or a break character
is detected. It is cleared by a software sequence (an read to the USART_SR register
followed by a read to the USART_DR register).
0: No Framing error is detected
1: Framing error or break character is detected

Note:This bit does not generate interrupt as it appears at the same time as the RXNE bit
which itself generates an interrupt. If the word currently being transferred causes both
frame error and overrun error, it will be transferred and only the ORE bit will be set.
An interrupt is generated on FE flag in case of Multi Buffer communication if the EIE bit
is set.
 */
#define USART_FE_EN					(1 << 1)
#define USART_FE_NE					(0 << 1)

// Parity error
/*
 This bit is set by hardware when a parity error occurs in receiver mode. It is cleared by a
software sequence (a read to the status register followed by a read to the USART_DR data
register). The software must wait for the RXNE flag to be set before clearing the PE bit.
An interrupt is generated if PEIE = 1 in the USART_CR1 register.
0: No parity error
1: Parity error
 */
#define USART_PE_EN					(1 << 0)
#define USART_PE_EN					(0 << 0)

/* End USART1_SR / USART2_SR */

/* Begin USART1_DR / USART2_DR */

// Data register
#define USART1_DR					(*(volatile uint32_t *)(CUSTOM_USART1_BASE + 0x04))
#define USART2_DR					(*(volatile uint32_t *)(CUSTOM_USART2_BASE + 0x04))

// Data value
// Adjusts for [8:0] open the port for you work
/*
 Contains the Received or Transmitted data character, depending on whether it is read from
or written to.
The Data register performs a double function (read and write) since it is composed of two
registers, one for transmission (TDR) and one for reception (RDR)
The TDR register provides the parallel interface between the internal bus and the output
shift register (see Figure 1).
The RDR register provides the parallel interface between the input shift register and the
internal bus.
When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
because it is replaced by the parity.
When receiving with the parity enabled, the value read in the MSB bit is the received parity
bit.
 */
#define USART_DR					(1 << 8)

/* End USART1_DR / USART2_DR */

/* Begin USART1_BRR / USART2_BRR */

// Baud rate register
/* Note:
 The baud counters stop counting if the TE or RE bits are disabled respectively. */
#define USART1_BRR					(*(volatile uint32_t *)(CUSTOM_USART1_BASE + 0x08))
#define USART2_BRR					(*(volatile uint32_t *)(CUSTOM_USART2_BASE + 0x08))


// Adjusts DIV_Mantissa[11:0] for open
/*
 mantissa of USARTDIV
These 12 bits define the mantissa of the USART Divider (USARTDIV)
 */
#define USART_DIV_Mantissa			(1 << 15)

// Adjusts DIV_Fraction[3:0] for open
/*
  fraction of USARTDIV
These 4 bits define the fraction of the USART Divider (USARTDIV)
 */
#define USART_DIV_Fraction			(1 << 3)

/* End USART1_BRR / USART2_BRR */

/* Begin USART1_CR1 / USART2_CR1 */

// Control register 1
#define USART1_CR1					(*(volatile uint32_t *)(CUSTOM_USART1_BASE + 0x0C))
#define USART2_CR1					(*(volatile uint32_t *)(CUSTOM_USART2_BASE + 0x0C))

// USART enable
/*
 When this bit is cleared the USART prescalers and outputs are stopped and the end of the
current
byte transfer in order to reduce power consumption. This bit is set and cleared by software.
0: USART prescaler and outputs disabled
1: USART enabled
 */
#define USART_UE					(1 << 13)

// Word length
/*
 This bit determines the word length. It is set or cleared by software.
0: 1 Start bit, 8 Data bits, n Stop bit
1: 1 Start bit, 9 Data bits, n Stop bit
Note: The M bit must not be modified during a data transfer (both transmission and reception)
 */
#define USART_M						(1 << 12)

// Wakeup method
/*
 This bit determines the USART wakeup method, it is set or cleared by software.
0: Idle Line
1: Address Mark
 */
#define USART_WAKE					(1 << 11)

// Parity control enable
/*
 This bit selects the hardware parity control (generation and detection). When the parity
control is enabled, the computed parity is inserted at the MSB position (9th bit if M=1; 8th bit
if M=0) and parity is checked on the received data. This bit is set and cleared by software.
Once it is set, PCE is active after the current byte (in reception and in transmission).
0: Parity control disabled
1: Parity control enabled
 */
#define USART_PCE					(1 << 10)

// Parity selection
/*
 This bit selects the odd or even parity when the parity generation/detection is enabled (PCE
bit set). It is set and cleared by software. The parity will be selected after the current byte.
0: Even parity
1: Odd parity
 */
#define USART_PS					(1 << 9)

// PE interrupt enable
/*
 This bit is set and cleared by software.
0: Interrupt is inhibited
1: A USART interrupt is generated whenever PE=1 in the USART_SR register
 */
#define USART_PEIE					(1 << 8)

// TXE interrupt enable
/*
 This bit is set and cleared by software.
0: Interrupt is inhibited
1: A USART interrupt is generated whenever TXE=1 in the USART_SR register
 */
#define USART_TXEIE					(1 << 7)

// Transmission complete interrupt enable
/*
 This bit is set and cleared by software.
0: Interrupt is inhibited
1: A USART interrupt is generated whenever TC=1 in the USART_SR register
 */
#define USART_TCIE					(1 << 6)

// RXNE interrupt enable
/*
 This bit is set and cleared by software.
0: Interrupt is inhibited
1: A USART interrupt is generated whenever ORE=1 or RXNE=1 in the USART_SR register
 */
#define USART_RXNEIE				(1 << 5)

// IDLE interrupt enable
/*
 This bit is set and cleared by software.
0: Interrupt is inhibited
1: A USART interrupt is generated whenever IDLE=1 in the USART_SR register
 */
#define USART_IDLEIE				(1 << 4)

// Transmitter enable
/*
 This bit enables the transmitter. It is set and cleared by software.
0: Transmitter is disabled
1: Transmitter is enabled
Note: 1: During transmission, a “0” pulse on the TE bit (“0” followed by “1”) sends a preamble
(idle line) after the current word, except in Smartcard mode.
2: When TE is set there is a 1 bit-time delay before the transmission starts.
 */
#define USART_TE					(1 << 3)

// Receiver enable
/*
 This bit enables the receiver. It is set and cleared by software.
0: Receiver is disabled
1: Receiver is enabled and begins searching for a start bit
 */
#define USART_RE					(1 << 2)

// Receiver wakeup
/*
 This bit determines if the USART is in mute mode or not. It is set and cleared by software and
can be cleared by hardware when a wakeup sequence is recognized.
0: Receiver in active mode
1: Receiver in mute mode
Note: 1: Before selecting Mute mode (by setting the RWU bit) the USART must first receive a
data byte, otherwise it cannot function in Mute mode with wakeup by Idle line detection.
2: In Address Mark Detection wakeup configuration (WAKE bit=1) the RWU bit cannot
be modified by software while the RXNE bit is set.
 */
#define USART_RWU					(1 << 1)

// Send break
/*
 This bit set is used to send break characters. It can be set and cleared by software. It should
be set by software, and will be reset by hardware during the stop bit of break.
0: No break character is transmitted
1: Break character will be transmitted
 */
#define USART_SBK					(1 << 0)

/* End USART1_CR1 / USART2_CR1 */

/* Begin USART1_CR2 / USART2_CR2 */

// Control register 2
#define USART1_CR2					(*(volatile uint32_t *)(CUSTOM_USART1_BASE + 0x10))
#define USART2_CR2					(*(volatile uint32_t *)(CUSTOM_USART2_BASE + 0x10))

// LIN mode enable
/*
 This bit is set and cleared by software.
0: LIN mode disabled
1: LIN mode enabled
The LIN mode enables the capability to send LIN Synch Breaks (13 low bits) using the SBK
bit in the USART_CR1 register, and to detect LIN Sync breaks.
 */
#define USART_LINEN					(1 << 14)

// STOP bits [Bits 13:12]
#define USART_STOP					(1 << 13)
// These bits are used for programming the stop bits.
/*
 00: 1 Stop bit
01: 0.5 Stop bit
10: 2 Stop bits
11: 1.5 Stop bit
The 0.5 Stop bit and 1.5 Stop bit are not available for UART4 & UART5.
 */
// 1 Stop bit
#define USART_1_Stop_bit			0x0
// 0.5 Stop bit
#define USART_0_5_Stop_bit			0x1
// 2 Stop bits
#define USART_2_Stop_bit			0x2
// 1.5 Stop bit
#define USART_1_5_Stop_bit			0x3

// Clock enable
/*
 This bit allows the user to enable the CK pin.
0: CK pin disabled
1: CK pin enabled
This bit is not available for UART4 & UART5.
 */
#define USART_CLKEN					(1 << 11)

// Clock polarity
/*
 This bit allows the user to select the polarity of the clock output on the CK pin in synchronous
mode. It works in conjunction with the CPHA bit to produce the desired clock/data
relationship
0: Steady low value on CK pin outside transmission window.
1: Steady high value on CK pin outside transmission window.
This bit is not available for UART4 & UART5.
 */
#define USART_CPOL					(1 << 10)

// Clock phase
/*
 This bit allows the user to select the phase of the clock output on the CK pin in synchronous
mode. It works in conjunction with the CPOL bit to produce the desired clock/data
relationship (see figures 290 to 291)
0: The first clock transition is the first data capture edge.
1: The second clock transition is the first data capture edge.
This bit is not available for UART4 & UART5.
 */
#define USART_CPHA					(1 << 9)

// Last bit clock pulse
/*
 This bit allows the user to select whether the clock pulse associated with the last data bit
transmitted (MSB) has to be output on the CK pin in synchronous mode.
0: The clock pulse of the last data bit is not output to the CK pin
1: The clock pulse of the last data bit is output to the CK pin
The last bit is the 8th or 9th data bit transmitted depending on the 8 or 9 bit format selected
by the M bit in the USART_CR1 register.
This bit is not available for UART4 & UART5.
 */
#define USART_LBCL					(1 << 8)

//  Reserved, forced by hardware to 0
#define USART_RESERVED_bit7

// LIN break detection interrupt enable
/*
 Break interrupt mask (break detection using break delimiter).
0: Interrupt is inhibited
1: An interrupt is generated whenever LBD=1 in the USART_SR register
 */
#define USART_LBDIE					(1 << 6)

// lin break detection length
/*
 This bit is for selection between 11 bit or 10 bit break detection.
0: 10 bit break detection
1: 11 bit break detection
 */
#define USART_LBDL					(1 << 5)

// Reserved, forced by hardware to 0
#define USART_RESERVED_bit4

// Address of the USART node
// Adjusts for ADD[3:0]
/*
 This bit-field gives the address of the USART node.
This is used in multiprocessor communication during mute mode, for wake up with address
mark detection.
 */
#define USART_ADD					(1 << 3)

// ------- Note: These 3 bits (CPOL, CPHA, LBCL) should not be written while the transmitter is enabled. -------

/* End USART1_CR2 / USART2_CR2 */

/* Begin USART1_CR3 / USART2_CR3 */

// Control register 3
#define USART1_CR3					(*(volatile uint32_t *)(CUSTOM_USART1_BASE + 0x14))
#define USART2_CR3					(*(volatile uint32_t *)(CUSTOM_USART2_BASE + 0x14))

// Reserved, forced by hardware to 0
#define USART_RESERVED_bit32_11

// CTS interrupt enable
/*
 0: Interrupt is inhibited
1: An interrupt is generated whenever CTS=1 in the USART_SR register
This bit is not available for UART4 & UART5.
 */
#define USART_CTSIE					(1 << 10)

// CTS enable
/*
 0: CTS hardware flow control disabled
1: CTS mode enabled, data is only transmitted when the CTS input is asserted (tied to 0). If
the CTS input is deasserted while a data is being transmitted, then the transmission is
completed before stopping. If a data is written into the data register while CTS is deasserted,
the transmission is postponed until CTS is asserted.
This bit is not available for UART4 & UART5.
 */
#define USART_CTSE					(1 << 9)

// RTS enable
/*
 0: RTS hardware flow control disabled
1: RTS interrupt enabled, data is only requested when there is space in the receive buffer.
The transmission of data is expected to cease after the current character has been
transmitted. The RTS output is asserted (tied to 0) when a data can be received.
This bit is not available for UART4 & UART5.
 */
#define USART_RTSE					(1 << 8)

// DMA enable transmitter
/*
 This bit is set/reset by software
1: DMA mode is enabled for transmission
0: DMA mode is disabled for transmission
This bit is not available for UART5.
 */
#define USART_DMAT					(1 << 7)

// DMA enable receiver
/*
 This bit is set/reset by software
1: DMA mode is enabled for reception
0: DMA mode is disabled for reception
This bit is not available for UART5.
 */
#define USART_DMAR					(1 << 6)

// Smartcard mode enable
/*
 This bit is used for enabling Smartcard mode.
0: Smartcard Mode disabled
1: Smartcard Mode enabled
This bit is not available for UART4 & UART5.
 */
#define USART_SCEN					(1 << 5)

// Smartcard NACK enable
/*
 0: NACK transmission in case of parity error is disabled
1: NACK transmission during parity error is enabled
This bit is not available for UART4 & UART5.
 */
#define USART_NACK					(1 << 4)

// Half-duplex selection
/*
 Selection of Single-wire Half-duplex mode
0: Half duplex mode is not selected
1: Half duplex mode is selected
 */
#define USART_HDSEL					(1 << 3)

// IrDA low-power
/*
 This bit is used for selecting between normal and low-power IrDA modes
0: Normal mode
1: Low-power mode
 */
#define USART_IRLP					(1 << 2)

// IrDA mode enable
/*
 This bit is set and cleared by software.
0: IrDA disabled
1: IrDA enabled
 */
#define USART_IREN					(1 << 1)

// Error interrupt enable
/*
 Error Interrupt Enable Bit is required to enable interrupt generation in case of a framing
error, overrun error or noise error (FE=1 or ORE=1 or NE=1 in the USART_SR register) in
case of Multi Buffer Communication (DMAR=1 in the USART_CR3 register).
0: Interrupt is inhibited
1: An interrupt is generated whenever DMAR=1 in the USART_CR3 register and FE=1 or
ORE=1 or NE=1 in the USART_SR register.
 */
#define USART_EIE					(1 << 0)

/* End USART1_CR3 / USART2_CR3 */

/* Begin USART1_GTPR / USART2_GTPR */

// Guard time and prescaler register
#define USART1_CR3					(*(volatile uint32_t *)(CUSTOM_USART1_BASE + 0x18))
#define USART2_CR3					(*(volatile uint32_t *)(CUSTOM_USART2_BASE + 0x18))

// Reserved, forced by hardware to 0
#define USART_RESERVED_bit31_16

// Guard time value
// Adjusts GT[7:0]
/*
 This bit-field gives the Guard time value in terms of number of baud clocks.
This is used in Smartcard mode. The Transmission Complete flag is set after this guard time
value.
This bit is not available for UART4 & UART5.
 */
#define USART_GT					(1 << 15)

// Prescaler value
// Adjusts for PSC[7:0]
/*
- In IrDA Low-power mode:
PSC[7:0] = IrDA Low-Power Baud Rate
Used for programming the prescaler for dividing the system clock to achieve the low-power
frequency:
The source clock is divided by the value given in the register (8 significant bits):
00000000: Reserved - do not program this value
00000001: divides the source clock by 1
00000010: divides the source clock by 2
 */
#define USART_PSC					(1 << 7)

// 00000000: Reserved - do not program this value
#define USART_PSC_RESERVED

// 00000001: divides the source clock by 1
#define USART_PSC_DIV_SRC_BY_1		(0x1U)

// 00000010: divides the source clock by 2
#define USART_PSC_DIV_SRC_BY_1		(0x2U)
// USART_PSC_DIV_SRC_BY_x ( ... )
/*
 – In normal IrDA mode: PSC must be set to 00000001.
– In Smartcard mode:

PSC[4:0]: Prescaler value
Used for programming the prescaler for dividing the system clock to provide the smartcard
clock.
The value given in the register (5 significant bits) is multiplied by 2 to give the division factor
of the source clock frequency:
00000: Reserved - do not program this value
00001: divides the source clock by 2
00010: divides the source clock by 4
00011: divides the source clock by 6
 */

// -------- Note: Bits [7:5] have no effect if Smartcard mode is used. This bit is not available for UART4 & UART5. --------

/* End USART1_GTPR / USART2_GTPR */

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
