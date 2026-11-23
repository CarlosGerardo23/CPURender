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

#define N_POINTS (9 * 9 * 9)

float fov_factor = 820;
bool is_running;
vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];

vec3_t camera_position = {0, 0, -10};
vec3_t cube_rotation = {0, 0, 0};
void setup_cube(void)
{
	int point_count = 0;
	for (float i = -1; i <= 1; i += 0.25)
	{
		for (float j = -1; j <= 1; j += 0.25)
		{
			for (float k = -1; k <= 1; k += 0.25)
			{
				vec3_t new_point = {.x = i, .y = j, .z = k};
				cube_points[point_count] = new_point;
				point_count++;
			}
		}
	}
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

vec2_t project(vec3_t point)
{
	vec2_t projected =
		{
			.x = (point.x * fov_factor) / point.z,
			.y = (point.y * fov_factor) / point.z};
	return projected;
}
void update_cube(void)
{
	cube_rotation.x += 0.005;
	cube_rotation.y += 0.005;
	cube_rotation.z += 0.005;

	for (size_t i = 0; i < N_POINTS; i++)
	{
		vec3_t point = cube_points[i];
		vec3_t transformed_point = rotate_x(point, cube_rotation.x);
		transformed_point = rotate_y(transformed_point, cube_rotation.y);
		transformed_point = rotate_z(transformed_point, cube_rotation.z);

		transformed_point.z -= camera_position.z;

		projected_points[i] = project(transformed_point);
	}
}

void render_cube(void)
{
	for (size_t i = 0; i < N_POINTS; i++)
	{
		vec2_t point = projected_points[i];
		draw_rect(color_buffer, window_width, window_height, point.x + (window_width / 2), point.y + (window_height / 2), 4, 4, 0xFFFFFF00);
	}
}
void update(void)
{
	// TO DO:
	update_cube();
}
void render(void)
{
	clear_color_buffer(0xFF000000, window_width, window_height);
	render_cube();
	// draw_rect(color_buffer, window_width, window_height, 20, 50, 100, 100, 0xFF00FFFF);
	// draw_pixel(color_buffer, window_width, 20, 20, 0xFFFFFF00);
	// draw_grid(color_buffer, window_width, window_height, 5, 0xFFFFFFFF);
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
int main(int argc, char *args[])
{
	is_running = initialize();
	setup_texture(window_width, window_height);
	setup_cube();

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
