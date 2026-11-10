#include "window.h"

SDL_Window *window = NULL;
int window_width = 500;
int window_height = 500;

bool initialize_window(void)
{
	bool result = false;
#ifdef __EMSCRIPTEN__
	result = initialize_window_web();
#else
	result = initialize_window_desktop();
#endif

	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_BORDERLESS);
	if (!window)
	{
		fprintf(stderr, "Error creating SDL Window\n");
		return false;
	}
	return true;
}

bool initialize_window_web(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		return false;
	}
}

bool initialize_window_desktop(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		return false;
	}
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);

	window_width = display_mode.w;
	window_height = display_mode.h;
}
void destroy_window(void)
{
	if (window)
	{
		SDL_DestroyWindow(window);
		window = NULL;
	}
}