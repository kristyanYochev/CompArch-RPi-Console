#include "uart.h"
#include "graphics.h"
// #include "homer.h"
#include "gpio.h"
#include "delay.h"
#include "spi.h"
#include "string.h"

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
    spi_init(32);

    unsigned char bytes[2] = {0xFA, 0xCE};
    char hex_string[3];

    for (int i = 0; i < 2; ++i) {
        unsigned char byte = spi_transfer(bytes[i]);
        byte_to_hex(byte, hex_string);

        draw_text(i*20, 10, hex_string, WHITE, BLACK);
    }
}
