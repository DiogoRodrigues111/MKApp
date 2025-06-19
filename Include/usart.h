/*
 * usart.h
 *
 *  Created on: Jun 12, 2025
 *      Author: Diogo R Roessler
 */

#ifndef INCLUDE_USART_H_
#define INCLUDE_USART_H_

#include "VERSION.h"

#ifdef __cplusplus
class USART_INFO_ABSTRATION_CXX {
public:
#if defined( USE_WITHOUT_HAL_ST )
	void Init_USART();
	void SendCmd(USART_INFO_ABSTRATION_CXX addrSignature, uint8_t addrValue);
	void RecvCmd(USART_INFO_ABSTRATION_CXX addrSignature, uint8_t addrValue);
#endif // USE_WITHOUT_HAL_ST
private:
	uint8_t* m_u8pUart_test = (volatile uint8_t)0x2C;
};
#endif // __cplusplus

#endif /* INCLUDE_USART_H_ */
