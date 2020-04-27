#include "i2c.h"
#include "graphics.h"

#define I2C_ERROR           ((*I2C_STATUS) & (1 << 8))
#define I2C_CLEAR_ERROR     *I2C_STATUS |= (1 << 8)

#define I2C_TIMEOUT         ((*I2C_STATUS) & (1 << 9))
#define I2C_CLEAR_TIMEOUT   *I2C_STATUS |= (1 << 9)

#define I2C_DONE            ((*I2C_STATUS) & (1 << 1))
#define I2C_CLEAR_DONE      *I2C_STATUS |= (1 << 1)

#define I2C_TXD             ((*I2C_STATUS) & (1 << 4))

void i2c_init()
{
    I2C_CLEAR_DONE;
    I2C_CLEAR_ERROR;
    I2C_CLEAR_TIMEOUT;

    // *I2C_CLK_DIV = 2500;

    set_pin_mode(2, ALT0);
    set_pin_mode(3, ALT0);
}

int i2c_write_bytes(unsigned char address, unsigned char * data, unsigned int length)
{
    *I2C_ADDRESS = address;
    *I2C_DATA_LEN = length;

    for (int i = 0; i < length; ++i)
    {
        *I2C_FIFO = data[i];
    }

    unsigned int r = 0;
    r &= ~(1 << 0); // Write transfer
    r |= (1 << 7); // Start transfer
    r |= (1 << 15); // Enable I2C
    *I2C_CONTROL = r;

    while (1)
    {
        if (I2C_ERROR)
        {
            I2C_CLEAR_DONE;
            I2C_CLEAR_ERROR;
            return 1;
        }
        if (I2C_TIMEOUT)
        {
            I2C_CLEAR_DONE;
            I2C_CLEAR_TIMEOUT;
            return 2;
        }
        if (I2C_DONE)
        {
            I2C_CLEAR_DONE;
            return 0;
        }
    }
}

int i2c_read_bytes(unsigned char address, unsigned int length, unsigned char * data)
{
    unsigned int r = 0;
    r |= (1 << 0); // Read transfer
    *I2C_CONTROL = r;

    *I2C_ADDRESS = address;
    *I2C_DATA_LEN = length;
    while (!((*I2C_STATUS) & (1 << 1))) ; // Wait until complete
    for (int i = 0; i < length; ++i)
    {
        data[i] = *I2C_FIFO;
    }
    return 0;
}
