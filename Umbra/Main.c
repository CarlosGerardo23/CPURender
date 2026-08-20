#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <stdbool.h>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool is_running = false;

uint32_t* color_buffer = NULL;

int window_width = 800;
int window_height = 600;
bool initialize_window(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		return false;
	}
	//Create window
	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_BORDERLESS);

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
void setup(void)
{
	color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);
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
void update(void)
{
	//TO DO:
}
void clear_color_buffer(uint32_t color)
{
	for(int y = 0; y < window_height; y ++)
	{
		for(int x = 0; x < window_width; x++)
		{
			color_buffer[(window_width*y) + x] = color
		}
	}
}
void render(void)
{
	SDL_SetRenderDrawColor(renderer, 0, 200, 100, 255);
	SDL_RenderClear(renderer);

	clear_color_buffer(0xFFFFFF00);
	SDL_RenderPresent(renderer);
}
void game_loop(void)
{
	process_input();
	update();
	render();
}
void destroy_window(void)
{
	free(color_buffer);
    color_buffer = NULL;

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    SDL_Quit();
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

	destroy_window();
	return 0;
}
