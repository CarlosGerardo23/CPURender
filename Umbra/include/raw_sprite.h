#ifndef RAW_SPRITE_H
#define RAW_SPRITE_H

#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <stdbool.h>

void draw_grid(uint32_t* color_buffer, int grid_size, uint32_t color);
void draw_rect(uint32_t* color_buffer, int x, int y, int width, int height, uint32_t color)

#endif