#include "uart.h"
#include "framebuffer.h"

void kernel_main()
{
    uart_init();
    fb_init();

    fb_showpicture();

    while(1);
}