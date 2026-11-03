#ifndef WINDOW_H
#define WINDOW_H
#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <stdbool.h>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

extern SDL_Window* window;
extern int window_width;
extern int window_height;

bool initialize_window(void);
void destroy_window(void);

#endif