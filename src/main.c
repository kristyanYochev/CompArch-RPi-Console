#include "uart.h"
#include "graphics.h"
// #include "homer.h"
#include "gpio.h"
#include "delay.h"
#include "spi.h"
#include "string.h"
#include "i2c.h"

void kernel_main()
{
    color_t WHITE = {
        .color_array = {0xFF, 0xFF, 0xFF, 0x00}
    };

    color_t BLACK = {
        .color_array = {0x00, 0x00, 0x00, 0x00}
    };

    uart_init();
    graphics_init();
    i2c_init();

    unsigned char bytes[2] = {0xFA, 0xCE};

    draw_text(0, 0, "Transfering...", WHITE, BLACK);

    int status = i2c_write_bytes(0x14, bytes, 2);

    switch(status)
    {
        case 0:
            draw_text(0, 30, "Transfer Done!", WHITE, BLACK);
            break;
        case 1:
            draw_text(0, 30, "Transfer ERR!", WHITE, BLACK);
            break;
        case 2:
            draw_text(0, 30, "Transfer TIMEOUT!", WHITE, BLACK);
            break;
        default:
            break;
    }
}
