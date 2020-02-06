#include "framebuffer.h"
#include "uart.h"
#include "mailbox.h"
#include "homer.h"

unsigned int width, height, pitch, isrgb;   /* dimensions and channel order */
unsigned char *fb;                         /* raw frame buffer address */

void fb_init()
{
    mailbox[0] = 35*4;
    mailbox[1] = MAILBOX_REQUEST;

    mailbox[2] = MAILBOX_TAG_SET_PHY_SIZE;
    mailbox[3] = 8;
    mailbox[4] = 8;
    mailbox[5] = 1024;         //FrameBufferInfo.width
    mailbox[6] = 768;          //FrameBufferInfo.height

    mailbox[7] = MAILBOX_TAG_SET_VIRT_SIZE;
    mailbox[8] = 8;
    mailbox[9] = 8;
    mailbox[10] = 1024;        //FrameBufferInfo.virtual_width
    mailbox[11] = 768;         //FrameBufferInfo.virtual_height

    mailbox[12] = MAILBOX_TAG_SET_VIRT_OFFSET;
    mailbox[13] = 8;
    mailbox[14] = 8;
    mailbox[15] = 0;           //FrameBufferInfo.x_offset
    mailbox[16] = 0;           //FrameBufferInfo.y.offset

    mailbox[17] = MAILBOX_TAG_SET_FB_DEPTH;
    mailbox[18] = 4;
    mailbox[19] = 4;
    mailbox[20] = 32;          //FrameBufferInfo.depth

    mailbox[21] = MAILBOX_TAG_SET_FB_PXORDR;
    mailbox[22] = 4;
    mailbox[23] = 4;
    mailbox[24] = 1;           //RGB, not BGR preferably

    mailbox[25] = MAILBOX_TAG_GET_FB;
    mailbox[26] = 8;
    mailbox[27] = 8;
    mailbox[28] = 4096;        //FrameBufferInfo.pointer
    mailbox[29] = 0;           //FrameBufferInfo.size

    mailbox[30] = MAILBOX_TAG_GET_FB_PITCH;
    mailbox[31] = 4;
    mailbox[32] = 4;
    mailbox[33] = 0;           //FrameBufferInfo.pitch

    mailbox[34] = MAILBOX_TAG_LAST;

    //this might not return exactly what we asked for, could be
    //the closest supported resolution instead
    if(mailbox_send(MAILBOX_CH_PROP) && mailbox[20]==32 && mailbox[28]!=0) {
        mailbox[28]&=0x3FFFFFFF;   //convert GPU address to ARM address
        width=mailbox[5];          //get actual physical width
        height=mailbox[6];         //get actual physical height
        pitch=mailbox[33];         //get number of bytes per line
        isrgb=mailbox[24];         //get the actual channel order
        fb=(void*)((unsigned long)mailbox[28]);
    } else {
        uart_puts("Unable to set screen resolution to 1024x768x32\n");
    }
}

void fb_showpicture()
{
    int x, y;

    // unsigned char * ptr = fb;
    char * data = homer_data;
    color_t pixel;

    // ptr += (height - homer_height) / 2 * pitch + (width - homer_width) * 2;
    for (y = 0; y < homer_height; ++y)
    {
        for (x = 0; x < homer_width; ++x)
        {
            HEADER_PIXEL(data, pixel.color_array)
            fb_write_pixel((width - homer_width) / 2 + x, (height - homer_height) / 2 + y, pixel);
        }
    }
}

void fb_write_pixel(unsigned int x, unsigned int y, color_t color)
{
    unsigned char * ptr = fb;
    ptr += y * pitch + x * 4;
    
    if (isrgb)
    {
        *((unsigned int *)ptr) = *((unsigned int *) &color.color);
    }
    else
    {
        // Flip R and B values (i.e cvt RGB to BGR)
        *((unsigned int *)ptr) = (unsigned int) (color.color_array[0] << 16 | color.color_array[1] << 8 | color.color_array[2]);
    }
}