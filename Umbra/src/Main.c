#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool is_running = false;
bool initialize_window(void)
{
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
	{
		fprintf(stderr , "Error initializing SDL.\n");
		return false;
	}
	//Create window
	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_BORDERLESS);

	if(!window)
	{
		fprintf(stderr, "Error creating SDL Window\n");
		return false;
	}

	//Create a SDL renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if(!renderer)
	{
		fprintf(stderr, "Error creating SDL Renderer\n");
		return false;
	}
	return true;
}

int main(int argc, char* args[])
{
	is_running = initialize_window();
	return 0;
}
