#include "raw_sprite.h"

void draw_grid(uint32_t *color_buffer, int window_width, int window_height, int grid_size, uint32_t color)
{
	for (int i = 0; i < window_height; i++)
	{
		for (int j = 0; j < window_width; j++)
		{
			if (i % grid_size == 0 || j % grid_size == 0)
			{
				color_buffer[(i*window_height)+j] = color;
			}
		}
	}
}

void draw_rect(uint32_t *color_buffer, int window_width, int window_height, int x, int y, int width, int height, uint32_t color)
{
	for(int i = y; i < height; i++)
	{
		for(int j = x; j < width; j++)
		{
			color_buffer[(i*window_height)+j] = color;
		}
	}
}