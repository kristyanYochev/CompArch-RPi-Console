#include "spi.h"
#include "gpio.h"

void spi_init(short clock_divisor)
{
    unsigned int r;

    r = *AUX_ENABLES;
    r |= 0b010; // Enable spi0
    *AUX_ENABLES = r;

    r = 0;
    r ^= (0b00 << 0);   // Chip Select 0
    r ^= (0b0 << 2);    // Clock phase middle
    r ^= (0b0 << 3);    // Clock polariy LOW
    r ^= (0b00 << 4);   // Clear FIFO no
    r ^= (0b0 << 6);    // Chip Select polarity LOW
    r ^= (0b0 << 7);    // Transfer inactive
    r ^= (0b0 << 8);    // DMA disabled
    r ^= (0b00 << 9);   // Disable interrupts
    r ^= (0b0 << 11);   // Disable ADCS
    r ^= (0b0 << 12);   // Read disable (int bidir mode only)
    r ^= (0b0 << 13);   // LoSSI disable

    *SPI_CS = r;

    *SPI_CLK = clock_divisor;

    for (int i = 7; i <= 11; ++i)
    {
        setPinMode(i, ALT0);
    }
}

unsigned char spi_transfer(unsigned char data)
{
    *SPI_CS |= (1 << 7); // Transfer active

    while(1)
    {
        if ((*SPI_CS) & (1<<18)) break;
    }
    *SPI_FIFO = data;

    unsigned char rv = 0x00;

    while (1) // while not done
    {
        if ((*SPI_CS) & (1 << 16)) break;
    }
    rv = *SPI_FIFO;

    *SPI_CS &= (1 << 7) ^ (0xFFFFFFFF); // Transfer incative

    return rv;
}
