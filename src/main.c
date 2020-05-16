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
    spi_init(0x3E);
    
    char bin_string[12];
    bin_string[0] = '\0';

    unsigned char recieved_byte;

    // draw_text(0, 0, "TRANFERED DATA", WHITE, BLACK);
    // draw_text(0, 30, hex_string, WHITE, BLACK);

    set_pin_mode(17, OUTPUT);
    digital_write(17, LOW);

    digital_write(17, HIGH);
    delay_us(1000000);

    while (1) {
        draw_text(0, 0, bin_string, WHITE, BLACK);
        digital_write(17, HIGH);
        delay_us(100000);

        recieved_byte = spi_transfer(0xFA);
        byte_to_bin(recieved_byte, bin_string);
        
        digital_write(17, LOW);
        clear_screen(BLACK);
    }
}
