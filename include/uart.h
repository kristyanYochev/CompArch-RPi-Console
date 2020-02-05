#ifndef __UART_H__
#define __UART_H__

void uart_init();
void uart_send(unsigned int c);
char uart_getc();
void uart_puts(const char * s);
void uart_hex(unsigned int d);

#endif