#include "uart.h"
#include "gpio.h"
#include "delay.h"
#include "mailbox.h"

#define UART0_DR        ((volatile unsigned int*)(MMIO_BASE+0x00201000))
#define UART0_FR        ((volatile unsigned int*)(MMIO_BASE+0x00201018))
#define UART0_IBRD      ((volatile unsigned int*)(MMIO_BASE+0x00201024))
#define UART0_FBRD      ((volatile unsigned int*)(MMIO_BASE+0x00201028))
#define UART0_LCRH      ((volatile unsigned int*)(MMIO_BASE+0x0020102C))
#define UART0_CR        ((volatile unsigned int*)(MMIO_BASE+0x00201030))
#define UART0_IMSC      ((volatile unsigned int*)(MMIO_BASE+0x00201038))
#define UART0_ICR       ((volatile unsigned int*)(MMIO_BASE+0x00201044))

void uart_init()
{
    register unsigned int r;

    mailbox[0] = 9 * 4;
    mailbox[1] = MAILBOX_REQUEST;
    mailbox[2] = MAILBOX_TAG_GETCLKRATE;
    mailbox[3] = 12;
    mailbox[4] = 8;
    mailbox[5] = MAILBOX_TAG_UARTCLK;
    mailbox[6] = 4000000;
    mailbox[7] = 0;
    mailbox[8] = MAILBOX_TAG_LAST;

    mailbox_send(MAILBOX_CH_PROP);

    r = *GPFSEL1;
    r &= ~((7 << 12) | (7 << 15)); // gpio14 & 15
    r |= (2 << 12) | (2 << 15); // alt5
    *GPFSEL1 = r;
    *GPPUD = 0; // set pull up/down
    delay_cycles(150);
    *GPPUDCLK0 = (1 << 14) | (1 << 15);
    delay_cycles(150);
    *GPPUDCLK0 = 0; // flush GPIO setup

    *UART0_ICR = 0x7FF;
    *UART0_IBRD = 2; // 115200 baud
    *UART0_FBRD = 0xB;
    *UART0_LCRH = 0b11 << 5;
    *UART0_CR = 0x301;
}

void uart_send(unsigned int c)
{
    while (!(*UART0_FR & 0x20)); // Wait your turn

    *UART0_DR = c;
}

char uart_getc()
{
    while (!(*UART0_FR & 0x01)); // Wait to get something

    return (char)(*UART0_DR);
}

void uart_puts(const char * s)
{
    for (int i = 0; s[i] != '\0'; ++i)
    {
        uart_send(s[i]);
    }
}

void uart_hex(unsigned int d)
{
    unsigned int n;
    int c;
    for (c = 28; c >= 0; --c)
    {
        n = (d >> c) & 0xF;
        n += (n > 9) ? 0x37 : 0x30;

        uart_send(n);
    }
}
