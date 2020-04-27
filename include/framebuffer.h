#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

typedef union color_t
{
    char color_array[4];
    unsigned int color;
    struct color
    {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
        unsigned char alpha;
    } color_struct;
} color_t;

void fb_init();
void fb_showpicture();
void fb_write_pixel(unsigned int x, unsigned int y, color_t color);
unsigned int get_screen_width();
unsigned int get_screen_height();

#endif