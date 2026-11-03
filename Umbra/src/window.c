#include "window.h"

SDL_Window* window = NULL;
int window_width = 500;
int window_height = 500;

bool initialize_window(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_BORDERLESS);
	if (!window)
	{
		fprintf(stderr, "Error creating SDL Window\n");
		return false;
	}
	return true;
}