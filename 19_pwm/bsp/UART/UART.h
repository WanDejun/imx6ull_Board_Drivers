#ifndef __UART_H
#define __UART_H

#include "config.h"
void UART_Init(UART_Type* UARTx);
inline void UART_Cmd(UART_Type* UARTx, uint32_t NewState);
inline void UART_SoftwareReset(UART_Type* UARTx);
inline void UART_putc(UART_Type* UARTx, char c);
inline char UART_getc(UART_Type* UARTx);
inline void UART_puts(UART_Type* UARTx, const char* str);

#endif
