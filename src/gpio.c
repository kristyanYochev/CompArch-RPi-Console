#include "gpio.h"

volatile unsigned int * FSEL_REGISTERS[6] = {
    GPFSEL0,
    GPFSEL1,
    GPFSEL2,
    GPFSEL3,
    GPFSEL4,
    GPFSEL5
};

volatile unsigned int * SET_REGISTERS[2] = {
    GPSET0,
    GPSET1
};

volatile unsigned int * CLR_REGISTERS[2] = {
    GPCLR0,
    GPCLR1
};

volatile unsigned int * LEV_REGISTERS[2] ={
    GPLEV0,
    GPLEV1
};

volatile unsigned int * PUDCLK_REGISTERS[2] ={
    GPPUDCLK0,
    GPPUDCLK1
};

void set_pin_mode(int pin, pin_mode_t pin_mode)
{
    unsigned int r;
    r = *(FSEL_REGISTERS[pin / 10]);
    r &= ~(0x7 << ((pin % 10) * 3));
    r |= pin_mode << ((pin % 10) * 3);
    *(FSEL_REGISTERS[pin / 10]) = r;
}

void digital_write(int pin, pin_state_t value)
{
    if (value == HIGH)
    {
        *(SET_REGISTERS[pin / 32]) = 0x1 << (pin % 32);
    }
    else
    {
        *(CLR_REGISTERS[pin / 32]) = 0x1 << (pin % 32);
    }
}

pin_state_t digital_read(int pin)
{
    return (*(LEV_REGISTERS[pin / 32]) >> (pin % 32)) & 0x1;
}

void set_pull_up_down(pull_up_down_t pd)
{
    *GPPUD = pd;
}

void set_pull_up_down_pin(int pin)
{
    *(PUDCLK_REGISTERS[pin / 32]) |= (1 << (pin % 32));
}