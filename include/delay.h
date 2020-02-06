#ifndef __DELAY_H__
#define __DELAY_H__

void delay_cycles(unsigned int cycles);
void delay_us(unsigned int delay);
unsigned long get_system_timer();
void delay_us_st(unsigned int delay);

#endif