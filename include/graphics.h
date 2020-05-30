#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#define HEADER_PIXEL(data,pixel) {\
pixel[0] = (((data[0] - 33) << 2) | ((data[1] - 33) >> 4)); \
pixel[1] = ((((data[1] - 33) & 0xF) << 4) | ((data[2] - 33) >> 2)); \
pixel[2] = ((((data[2] - 33) & 0x3) << 6) | ((data[3] - 33))); \
data += 4; \
}

#include "framebuffer.h"

void graphics_init();
void draw_rectangle(unsigned int x, unsigned int y, unsigned int w, unsigned int h, color_t color);
void draw_image(char * data, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
void draw_text(unsigned int x, unsigned int y, const char * text, color_t text_color, color_t bg_color);
void clear_text(unsigned int x, unsigned int y, const char * text, color_t color);
void clear_screen();
void show_screen();

#endif