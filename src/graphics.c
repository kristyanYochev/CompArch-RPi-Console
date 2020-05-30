#include "graphics.h"
#include "framebuffer.h"

typedef struct {
    unsigned int magic;
    unsigned int version;
    unsigned int headersize;
    unsigned int flags;
    unsigned int numglyph;
    unsigned int bytesperglyph;
    unsigned int height;
    unsigned int width;
    unsigned char glyphs;
} __attribute__((packed)) psf_t;
extern volatile unsigned char _font_data;

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

void draw_character(int x, int y, char c, color_t text_color, color_t bg_color)
{
    psf_t * font = (psf_t *) &_font_data;

    unsigned char * glyph = (unsigned char *) &_font_data +
        font->headersize + (c < font->numglyph ? c : 0) * font->bytesperglyph;

    int mask, bytes_per_line = (font->width + 7) / 8;

    if (c == '\r')
    {
        x = 0;
    }
    else if (c == '\n')
    {
        x = 0;
        ++y;
    }
    else
    {
        for (int j = y; j < y + font->height; ++j)
        {
            mask = 1 << (font->width - 1);
            for (int i = x; i < x + font->width; ++i)
            {
                fb_write_pixel(i, j, (((int)*glyph) & mask) ? text_color : bg_color);
                mask >>= 1;
            }
            glyph += bytes_per_line;
        }
    }
}

void draw_text(unsigned int x, unsigned int y, const char * text, color_t text_color, color_t bg_color)
{
    unsigned int start_x = x;
    psf_t * font = (psf_t *) &_font_data;
    for (int i = 0; text[i] != '\0'; ++i)
    {
        if (text[i] == '\n')
        {
            x = start_x;
            y += font->height;
        }
        else
        {
            draw_character(x, y, text[i], text_color, bg_color);
            x += font->width;
        }
    }
}

void clear_text(unsigned int x, unsigned int y, const char * text, color_t color)
{
    unsigned int start_x = x;
    psf_t * font = (psf_t *) &_font_data; 
    for (int i = 0; text[i] != '\0'; ++i)
    {
        if (text[i] == '\n')
        {
            x = start_x;
            y += font->height;
        }
        else
        {
            draw_rectangle(x, y, font->width, font->height, color);
            x += font->width;
        }
        
    }
}

void clear_screen()
{
    fb_clear();
}

void show_screen()
{
    fb_show();
}