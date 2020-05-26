#ifndef __MAILBOX_H__
#define __MAILBOX_H__

volatile unsigned int __attribute__((aligned(16))) mailbox[36];

#define MAILBOX_REQUEST     0

#define MAILBOX_CH_POWER    0
#define MAILBOX_CH_FB       1
#define MAILBOX_CH_VUART    2
#define MAILBOX_CH_VCHIQ    3
#define MAILBOX_CH_LEDS     4
#define MAILBOX_CH_BTNS     5
#define MAILBOX_CH_TOUCH    6
#define MAILBOX_CH_COUNT    7
#define MAILBOX_CH_PROP     8

#define MAILBOX_TAG_GETSERIAL       0x10004
#define MAILBOX_TAG_GETCLKRATE      0x38002
#define MAILBOX_TAG_SETPOWER        0x28001
#define MAILBOX_TAG_SET_PHY_SIZE    0x48003
#define MAILBOX_TAG_SET_VIRT_SIZE   0x48004
#define MAILBOX_TAG_SET_VIRT_OFFSET 0x48009
#define MAILBOX_TAG_SET_FB_DEPTH    0x48005
#define MAILBOX_TAG_SET_FB_PXORDR   0x48006
#define MAILBOX_TAG_GET_FB          0x40001
#define MAILBOX_TAG_GET_FB_PITCH    0x40008
#define MAILBOX_TAG_UARTCLK         2
#define MAILBOX_TAG_LAST            0

#define MAILBOX_TAG_BLANK_SCREEN    0x40002

int mailbox_send(unsigned char channel);

#endif
