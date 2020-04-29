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
    // spi_init(0x05DC);
    spi_init(0);
    
    char hex_string[12];

    unsigned char recieved_byte = spi_transfer(0xFA);

    byte_to_bin(recieved_byte, hex_string);

    draw_text(0, 0, "TRANFERED DATA", WHITE, BLACK);
    draw_text(0, 30, hex_string, WHITE, BLACK);
    
    while (1);
}
