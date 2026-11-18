#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <stdbool.h>

#include "renderer.h"
#include "window.h"
#include "raw_sprite.h"

#include "vector.h"
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

bool is_running;

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
void render(void)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	clear_color_buffer(0xFF000000, window_width, window_height);
	draw_rect(color_buffer,window_width,window_height,20,50,100,100, 0xFF00FFFF);
	draw_pixel(color_buffer, window_width, 20, 20, 0xFFFFFF00);
	draw_grid(color_buffer, window_width, window_height, 50, 0xFFFFFFFF);
	render_color_buffer(window_width);
	SDL_RenderPresent(renderer);
}
void game_loop(void)
{
	process_input();
	update();
	render();
}
bool initialize()
{
	bool result = false;

	result = initialize_window();
	result = initialize_renderer(window);
	return result;
}

void destroy(void)
{
	destroy_renderer();
	destroy_window();
	SDL_Quit();
}
int main(int argc, char* args[])
{
	is_running = initialize();
	setup_texture(window_width, window_height);

	vec3_t test = {2.0, 1.0, -1.0};
#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(game_loop, 0, 1);
#else
	while (is_running)
	{
		game_loop();
	}
#endif
    destroy();
	return 0;
}
