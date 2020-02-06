#include "uart.h"
#include "graphics.h"
// #include "homer.h"
#include "gpio.h"
#include "delay.h"

void kernel_main()
{
    uart_init();
    graphics_init();

    color_t RED = {
        .color_array = {0xFF, 0x00, 0x00, 0x00}
    };

    color_t WHITE = {
        .color_array = {0xFF, 0xFF, 0xFF, 0x00}
    };

    color_t BLACK = {
        .color_array = {0x00, 0x00, 0x00, 0x00}
    };

    // draw_rectangle(100, 100, 100, 100, RED);

    // draw_image(homer_data, 100, 100, homer_width, homer_height);

    draw_text(100, 100, "- Hello World!\n- I have a GF.", RED, BLACK);

    setPinMode(4, OUTPUT);

    while(1)
    {
        digitalWrite(4, HIGH);
        delay_us_st(1000000);
        digitalWrite(4, LOW);
        delay_us_st(1000000);
    }
}
