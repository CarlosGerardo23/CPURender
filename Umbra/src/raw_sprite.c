#include "raw_sprite.h"

void draw_grid(uint32_t* color_buffer,int window_width, int window_height, int grid_size, uint32_t color)
{
    for(int y = 0; y < window_height; y++)
    {
        for(int x = 0; < window_width; x++)
        {
            if(x % grid_size == 0 || y % grid_size == 0)
            {
                color_buffer[(window_height * y) + x] = color;
            }
        }
    }
}

void draw_rect(uint32_t* color_buffer,int window_width, int window_height, 
    int x, int y, int width, int height, uint32_t color)
{
    for(int i = y; i < y + height; i++)
    {
        for(int j = x; j < x + width; j++)
        {
            color_buffer[(window_height * i) + j] = color;
        }
    }
}