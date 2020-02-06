#include "graphics.h"
#include "framebuffer.h"

void graphics_init()
{
    fb_init();
}

void draw_rectangle(unsigned int start_x, unsigned int start_y, unsigned int w, unsigned int h, color_t color)
{
    for (int y = start_y; y < start_y + h; ++y)
    {
        for (int x = start_x; x < start_x + w; ++x)
        {
            fb_write_pixel(x, y, color);
        }
    }
}

void draw_image(char * img_data, unsigned int start_x, unsigned int start_y, unsigned int w, unsigned int h)
{
    color_t curr_pixel;

    for (int y = start_y; y < start_y + h; ++y)
    {
        for (int x = start_x; x < start_x + w; ++x)
        {
            HEADER_PIXEL(img_data, curr_pixel.color_array);
            fb_write_pixel(x, y, curr_pixel);
        }
    }
}
