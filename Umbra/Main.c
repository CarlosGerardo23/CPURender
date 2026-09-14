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

SDL_Texture* color_buffer_texture = NULL;

bool initialize_window(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		return false;
	}
	// Use SDL to query the current display mode and set the window width and height accordingly
	
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);

	window_width = display_mode.w;
	window_height = display_mode.h;

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

	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	return true;
}
void setup(void)
{
	color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
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
void draw_grid(int grid_size)
{
	for (int y = 0; y < window_height; y++)
	{
		for (int x = 0; x < window_width; x++)
		{
			if (y % grid_size == 0 || x % grid_size == 0)
			{
				color_buffer[(window_width * y) + x] = 0xFFFFFFFF; 
			}
		}
	}
}
void draw_rect(int x, int y, int width, int height, uint32_t color)
{
	for(int i = y; i < y + height; i++)
	{
		for(int j = x; j < x + width; j++)
		{				
			color_buffer[(window_width * i) + j] = color;
		}
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
			color_buffer[(window_width*y) + x] = color;
		}
	}
}
void render_color_buffer(void)
{
	SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)(window_width * sizeof(uint32_t)));
	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}
void render(void)
{
	SDL_SetRenderDrawColor(renderer, 0, 200, 100, 255);
	SDL_RenderClear(renderer);
    
	//draw_grid(50);
	draw_rect(300,200,300,150, 0xFFFF00FF);
	render_color_buffer();
	clear_color_buffer(0xFF000000);
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
