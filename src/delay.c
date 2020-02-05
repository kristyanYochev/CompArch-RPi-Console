#include "delay.h"
#include "gpio.h"

#define SYSTMR_LO        ((volatile unsigned int*)(MMIO_BASE+0x00003004))
#define SYSTMR_HI        ((volatile unsigned int*)(MMIO_BASE+0x00003008))

void delay_cycles(unsigned int cycles)
{
    while(cycles--)
    {
        asm volatile("nop");
    }
}

void delay_us(unsigned int delay)
{
    register unsigned long f, t, r;

    asm volatile("mrs %0, cntfrq_el0" : "=r"(f));
    asm volatile("mrs %0, cntpct_el0" : "=r"(t));

    t += ((f / 1000) * delay) / 1000;

    do
    {
        asm volatile("mrs %0, cntpct_el0" : "=r"(r));
    }
    while(r < t);
}

unsigned long get_system_timer()
{
    unsigned int h = -1, l;

    h = *SYSTMR_HI;
    l = *SYSTMR_LO;

    if (h != *SYSTMR_HI)
    {
        h = *SYSTMR_HI;
        l = *SYSTMR_LO;
    }

    return ((unsigned long) h << 32) | l;
}

void delay_ms_st(unsigned int delay)
{
    unsigned long t = get_system_timer();

    if(t)
    {
        while (get_system_timer() < t + delay);
    }
}