#ifndef __UART_PRINT_H
#define __UART_PRINT_H

void UART_print_Init();
void putc(char c);
char getc(void);
void puts(const char* str);

#endif
