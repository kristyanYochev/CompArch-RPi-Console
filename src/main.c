#include "uart.h"
#include "framebuffer.h"
#include "gpio.h"
#include "delay.h"

void kernel_main()
{
    uart_init();
    fb_init();

    fb_showpicture();

    setPinMode(4, OUTPUT);

    while(1)
    {
        digitalWrite(4, HIGH);
        delay_ms_st(1000000);
        digitalWrite(4, LOW);
        delay_ms_st(1000000);
    }
}
