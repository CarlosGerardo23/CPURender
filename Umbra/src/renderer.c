#include "renderer.h"

bool initialize_renderer(SDL_Window* window)
{
    renderer = SDL_CreateRenderer(window, -1 , 0);
    if(!renderer)
    {
        fprintf(stderr, "Error creating SDL Renderer");
        return false;
    }
    return true;
}

void setup_texture(int window_width, int window_height)
{
    color_buffer = (uint32_t)* malloc(sizeof(uint32_t) * window_width * window_height);
    color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
}
void render_color_buffer(void);
{
    SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)(window_width*sizeof(uint32_t)));
    SDL_RenderCopy(renderer, color_buffer_texture,NULL,NULL);
}
void clear_color_buffer(uint32_t color, int window_width, int window_height)
{
    for(int i = 0; i < window_height; i++)
    {
        for(int j = 0; j < window_width; j++)
        {
            color_buffer[(window_height*i)+j] = color;
        }
    }
}
void destroy_renderer(void)
{
    free(color_buffer);
    color_buffer = NULL;

    if(renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
}