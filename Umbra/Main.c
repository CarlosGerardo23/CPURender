#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool is_running = false;
bool initialize_window(void)
{
	if(SDL_Init(SDL_INIT_VIDEO)!=0)
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
void setup()
{
	//TO DO:
}
void process_input()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		is_running = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			is_running = false;
			break;
		}
	default:
		break;
	}
}
void update()
{
	//TO DO:
}
void render()
{
	SDL_SetRenderDrawColor(renderer, 0, 200, 100, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}
void game_loop()
{
	process_input();
	update();
	render();
}
int main(int argc, char* args[])
{
	is_running = initialize_window();
	setup();
#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(game_loop, 0, 1);
#else
	while (is_running)
	{
		game_loop();
	}
#endif
	return 0;
}
