#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

typedef union {
    unsigned char raw_data;
    struct input_data_t {
        unsigned char a: 1;
        unsigned char b: 1;
        unsigned char select: 1;
        unsigned char start: 1;
        unsigned char left: 1;
        unsigned char down: 1;
        unsigned char right: 1;
        unsigned char up: 1;
    } input_data;
} controller_input_t;

controller_input_t get_controller_state(short controller_number);

#endif