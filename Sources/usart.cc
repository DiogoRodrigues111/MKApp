/*
 * usart.cc
 *
 *  Created on: Jun 12, 2025
 *      Author: Diogo R Roessler
 */

#include "serialize.h"
#include "usart.h"
#include "VERSION.h"

namespace PROTOCOLS_USART_SYSTEM {

#if defined( USE_WITHOUT_HAL_ST )

/**
 * Initialization USART Protocol
 */
void USART_INFO_ABSTRATION_CXX::Init_USART() {
	CUSTOM_RCC_APB2ENR |= CUSTOM_RCC_APB2ENR_IOPAEN | CUSTOM_RCC_APB2ENR_USART1EN;

}

/**
 * Send/Transmit USART command
 */
void USART_INFO_ABSTRATION_CXX::SendCmd(
		USART_INFO_ABSTRATION_CXX addrSignature,
		void* addrValue)
{

}

/**
 * Received USART command
 */
void USART_INFO_ABSTRATION_CXX::RecvCmd(
		USART_INFO_ABSTRATION_CXX addrSignature,
		void* addrValue)
{

}

#endif // USE_WITHOUT_HAL_ST
}
