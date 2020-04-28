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
    spi_init(0x05DC);

    spi_send_byte_async(0xFA);
    delay_cycles(10000);
    spi_send_byte_async(0xCE);

    draw_text(0, 0, "DONE TRANSFER", WHITE, BLACK);
    
    while (1);
}
