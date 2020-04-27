#ifndef __GPIO_H__
#define __GPIO_H__

#define MMIO_BASE   0x3F000000

#define GPFSEL0     ((volatile unsigned int*)(MMIO_BASE+0x00200000))
#define GPFSEL1     ((volatile unsigned int*)(MMIO_BASE+0x00200004))
#define GPFSEL2     ((volatile unsigned int*)(MMIO_BASE+0x00200008))
#define GPFSEL3     ((volatile unsigned int*)(MMIO_BASE+0x0020000C))
#define GPFSEL4     ((volatile unsigned int*)(MMIO_BASE+0x00200010))
#define GPFSEL5     ((volatile unsigned int*)(MMIO_BASE+0x00200014))
#define GPSET0      ((volatile unsigned int*)(MMIO_BASE+0x0020001C))
#define GPSET1      ((volatile unsigned int*)(MMIO_BASE+0x00200020))
#define GPCLR0      ((volatile unsigned int*)(MMIO_BASE+0x00200028))
#define GPCLR1      ((volatile unsigned int*)(MMIO_BASE+0x0020002C))
#define GPLEV0      ((volatile unsigned int*)(MMIO_BASE+0x00200034))
#define GPLEV1      ((volatile unsigned int*)(MMIO_BASE+0x00200038))
#define GPEDS0      ((volatile unsigned int*)(MMIO_BASE+0x00200040))
#define GPEDS1      ((volatile unsigned int*)(MMIO_BASE+0x00200044))
#define GPHEN0      ((volatile unsigned int*)(MMIO_BASE+0x00200064))
#define GPHEN1      ((volatile unsigned int*)(MMIO_BASE+0x00200068))
#define GPPUD       ((volatile unsigned int*)(MMIO_BASE+0x00200094))
#define GPPUDCLK0   ((volatile unsigned int*)(MMIO_BASE+0x00200098))
#define GPPUDCLK1   ((volatile unsigned int*)(MMIO_BASE+0x0020009C))

typedef enum pin_mode
{
    INPUT = 0x0,
    OUTPUT = 0x1,
    ALT0 = 0x4,
    ALT1 = 0x5,
    ALT2 = 0x6,
    ALT3 = 0x7,
    ALT4 = 0x3,
    ALT5 = 0x2
} pin_mode_t;

typedef enum pin_state
{
    HIGH = 1,
    LOW = 0
} pin_state_t;

typedef enum pull_up_down
{
    PD_OFF = 0,
    PD_DOWN = 1,
    PD_UP = 2
} pull_up_down_t;

extern volatile unsigned int * FSEL_REGISTERS[6];
extern volatile unsigned int * SET_REGISTERS[2];
extern volatile unsigned int * CLR_REGISTERS[2];
extern volatile unsigned int * LEV_REGISTERS[2];

void set_pin_mode(int pin, pin_mode_t pin_mode);
void digital_write(int pin, pin_state_t value);
pin_state_t digital_read(int pin);
void set_pull_up_down(pull_up_down_t pd);
void set_pull_up_down_pin(int pin);

#endif