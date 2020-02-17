#ifndef __SPI_H__
#define __SPI_H__

#include "gpio.h"

#define SPI_BASE        (MMIO_BASE + 0x00204000)
#define AUX_ENABLES     ((volatile unsigned int *)(MMIO_BASE + 0x00215004))

#define SPI_CS          ((volatile unsigned int *)(SPI_BASE + 0x00))
#define SPI_FIFO        ((volatile unsigned int *)(SPI_BASE + 0x04))
#define SPI_CLK         ((volatile unsigned int *)(SPI_BASE + 0x08))
#define SPI_DLEN        ((volatile unsigned int *)(SPI_BASE + 0x0c))
#define SPI_LTOH        ((volatile unsigned int *)(SPI_BASE + 0x10))
#define SPI_DC          ((volatile unsigned int *)(SPI_BASE + 0x14))

void spi_init(short clock_divisor);
unsigned char spi_transfer(unsigned char data);

#endif