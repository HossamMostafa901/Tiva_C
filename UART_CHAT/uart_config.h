/*
 * uart_config.h
 *
 *  Created on: Sep 2, 2023
 *      Author: ZYZ
 */

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#define TIVA_UART           UART3_BASE
#define TERMINAL_UART       UART0_BASE

void UART_init(void);

void UART_initTerminal(void);

void UART_sendString(const uint8_t *Str, uint32_t uartUsed);

void UART_receiveString(uint8_t *Str, uint32_t uartUsed);

void PORTF_INIT(void);

void UART_OFF(void);

void UART_ON(void);

#endif /* UART_CONFIG_H_ */
