#ifndef __I2C_H__
#define __I2C_H__

#include "gpio.h"

#define I2C_BASE        (MMIO_BASE + 0x00804000)

#define I2C_CONTROL     ((volatile unsigned int *)(I2C_BASE + 0x00))
#define I2C_STATUS      ((volatile unsigned int *)(I2C_BASE + 0x04))
#define I2C_DLEN        ((volatile unsigned int *)(I2C_BASE + 0x08))
#define I2C_ADDRESS     ((volatile unsigned int *)(I2C_BASE + 0x0C))
#define I2C_FIFO        ((volatile unsigned int *)(I2C_BASE + 0x10))
#define I2C_CLK_DIV     ((volatile unsigned int *)(I2C_BASE + 0x14))
#define I2C_DATA_LEN    ((volatile unsigned int *)(I2C_BASE + 0x18))
#define I2C_CLK_TIMEOUT ((volatile unsigned int *)(I2C_BASE + 0x1c))

void i2c_init();
int i2c_write_bytes(unsigned char address, unsigned char * data, unsigned int length);
int i2c_read_bytes(unsigned char address, unsigned int length, unsigned char * data);

#endif