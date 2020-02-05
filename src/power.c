#include "power.h"
#include "gpio.h"
#include "mailbox.h"
#include "delay.h"

#define PM_RSTC         ((volatile unsigned int*)(MMIO_BASE+0x0010001c))
#define PM_RSTS         ((volatile unsigned int*)(MMIO_BASE+0x00100020))
#define PM_WDOG         ((volatile unsigned int*)(MMIO_BASE+0x00100024))
#define PM_WDOG_MAGIC   0x5a000000
#define PM_RSTC_FULLRST 0x00000020

void power_off()
{
    unsigned long r;

    for (r = 0; r < 16; r++)
    {
        mailbox[0]=8*4;
        mailbox[1]=MAILBOX_REQUEST;
        mailbox[2]=MAILBOX_TAG_SETPOWER; // set power state
        mailbox[3]=8;
        mailbox[4]=8;
        mailbox[5]=(unsigned int)r; // device id
        mailbox[6]=0; // bit 0: off, bit 1: no wait
        mailbox[7]=MAILBOX_TAG_LAST;
        mailbox_send(MAILBOX_CH_PROP);
    }

    *GPFSEL0 = 0;
    *GPFSEL1 = 0;
    *GPFSEL2 = 0;
    *GPFSEL3 = 0;
    *GPFSEL4 = 0;
    *GPFSEL5 = 0;
    *GPPUD = 0;
    delay_cycles(150);
    *GPPUDCLK0 = 0xFFFFFFFF;
    *GPPUDCLK1 = 0xFFFFFFFF;
    delay_cycles(150);
    *GPPUDCLK0 = 0;
    *GPPUDCLK1 = 0;

    r = *PM_RSTS;
    r &= ~0xFFFFFAAA;
    r |= 0x555;
    *PM_RSTS = PM_WDOG_MAGIC | r;
    *PM_WDOG = PM_WDOG_MAGIC | 10;
    *PM_RSTC = PM_WDOG_MAGIC | PM_RSTC_FULLRST;
}

void reset()
{
    unsigned int r;

    r = *PM_RSTS;
    r &= ~0xFFFFFAAA;
    *PM_RSTS = PM_WDOG_MAGIC | r;
    *PM_WDOG = PM_WDOG_MAGIC | 10;
    *PM_RSTC = PM_WDOG_MAGIC | PM_RSTC_FULLRST;
}
