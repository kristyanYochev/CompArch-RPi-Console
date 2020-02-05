#include "mailbox.h"
#include "gpio.h"

#define VIDEOCORE_MAILBOX   (MMIO_BASE + 0x0000B880)
#define MAILBOX_READ        ((volatile unsigned int*)(VIDEOCORE_MAILBOX+0x0))
#define MAILBOX_POLL        ((volatile unsigned int*)(VIDEOCORE_MAILBOX+0x10))
#define MAILBOX_SENDER      ((volatile unsigned int*)(VIDEOCORE_MAILBOX+0x14))
#define MAILBOX_STATUS      ((volatile unsigned int*)(VIDEOCORE_MAILBOX+0x18))
#define MAILBOX_CONFIG      ((volatile unsigned int*)(VIDEOCORE_MAILBOX+0x1C))
#define MAILBOX_WRITE       ((volatile unsigned int*)(VIDEOCORE_MAILBOX+0x20))
#define MAILBOX_RESPONSE    0x80000000
#define MAILBOX_FULL        0x80000000
#define MAILBOX_EMPTY       0x40000000

int mailbox_send(unsigned char channel)
{
    unsigned int r = (((unsigned int)((unsigned long)&mailbox) & ~0xF) | (channel & 0xF));

    while(*MAILBOX_STATUS & MAILBOX_FULL);
    *MAILBOX_WRITE = r;

    while(1)
    {
        while(*MAILBOX_STATUS & MAILBOX_EMPTY);
        if (r == *MAILBOX_READ)
        {
            return mailbox[1] == MAILBOX_RESPONSE;
        }
    }
}
