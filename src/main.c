#include "uart.h"
#include "graphics.h"
// #include "homer.h"
#include "gpio.h"
#include "delay.h"
#include "spi.h"
#include "string.h"
#include "i2c.h"

typedef union controller_input_t {
    struct buttons_t {
        char a: 1;
        char b: 1;
        char start: 1;
        char select: 1;
        char left: 1;
        char down: 1;
        char right: 1;
        char up: 1;
    } buttons;
    unsigned char repr_byte;
} controller_input_t;

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
    spi_init(0x3E);
    
    char bin_string[12];
    bin_string[0] = '\0';

    unsigned char input;

    // draw_text(0, 0, "TRANFERED DATA", WHITE, BLACK);
    // draw_text(0, 30, hex_string, WHITE, BLACK);

    while (1) {
        byte_to_bin(input, bin_string);
        input = spi_transfer(0xAC);
        
        delay_us(1000000 / 60);

        clear_screen(BLACK);
        draw_text(0, 0, bin_string, WHITE, BLACK);
        show_screen();
    }
}
