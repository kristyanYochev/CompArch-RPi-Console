#include "uart.h"
#include "graphics.h"
// #include "homer.h"
#include "gpio.h"
#include "delay.h"
#include "spi.h"
#include "string.h"
#include "i2c.h"
#include "game.h"
#include "mailbox.h"
#include "power.h"

void kernel_main()
{
    uart_init();
    graphics_init();
    spi_init(0x3E);

    start_game();

    power_off();
}
