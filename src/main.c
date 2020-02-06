#include "uart.h"
#include "graphics.h"
#include "homer.h"
#include "gpio.h"
#include "delay.h"

void kernel_main()
{
    uart_init();
    graphics_init();

    // color_t RED = {
    //     .color_array = {0xFF, 0x00, 0x00, 0x00}
    // };

    // draw_rectangle(100, 100, 100, 100, RED);

    draw_image(homer_data, 100, 100, homer_width, homer_height);

    setPinMode(4, OUTPUT);

    while(1)
    {
        digitalWrite(4, HIGH);
        delay_ms_st(1000000);
        digitalWrite(4, LOW);
        delay_ms_st(1000000);
    }
}
