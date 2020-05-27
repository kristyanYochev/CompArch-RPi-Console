#include "uart.h"
#include "graphics.h"
// #include "homer.h"
#include "gpio.h"
#include "delay.h"
#include "spi.h"
#include "string.h"
#include "i2c.h"
#include "game.h"

void kernel_main()
{
    uart_init();
    graphics_init();
    spi_init(0x3E);
    
    // char bin_string[12];
    // bin_string[0] = '\0';

    // unsigned char input;

    // // draw_text(0, 0, "TRANFERED DATA", WHITE, BLACK);
    // // draw_text(0, 30, hex_string, WHITE, BLACK);

    // while (1) {
    //     byte_to_bin(input, bin_string);
    //     input = spi_transfer(0xAC);
        
    //     delay_us(1000000 / 60);

    //     clear_screen(BLACK);
    //     draw_text(0, 0, bin_string, WHITE, BLACK);
    //     show_screen();
    // }

    start_game();

    while (1);
}
