#ifndef WINDOW_H
#define WINDOW_H
#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <stdbool.h>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int window_width = 1000;
int window_height = 1000;

bool initialize_window(void);
void destroy_window(void);

#endif