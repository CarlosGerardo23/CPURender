#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <stdbool.h>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif



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
	free(color_buffer);
    color_buffer = NULL;

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    // if (window)
    // {
    //     SDL_DestroyWindow(window);
    //     window = NULL;
    // }

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
