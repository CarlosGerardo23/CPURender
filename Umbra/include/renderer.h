#ifndef RENDERER_H
#define RENDERER_H
#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <stdbool.h>

uint32_t* color_buffer;
SDL_Texture* color_buffer_texture;
SDL_Renderer* renderer;

bool initialize_renderer(SDL_Window* window);
void setup_texture(int window_width, int window_height);
void clear_color_buffer(uint32_t color, int window_width, int window_height);
void render_color_buffer(int window_width);
void destroy_renderer(void);
#endif