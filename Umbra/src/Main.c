#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <stdbool.h>

#include "renderer.h"
#include "window.h"
#include "raw_sprite.h"

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
	draw_rect(50,0,400,400, 0xFFFF00FF);
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
	destroy_renderer();
	destroy_window();
}

bool initialize()
{
	bool result = false;

	result = initialize_window();
	result = initialize_renderer(window);
	return result;
}

int main(int argc, char* args[])
{
	is_running = initialize();
	setup_texture();
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
