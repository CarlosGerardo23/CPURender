#include "window.h"

bool initialize_window(void)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return false;
        #ifndef __EMSCRIPTEN__
        
        SDL_DisplayMode display_mode;
        SDL_GetCurrentDisplayMode(0, &display_mode);
        window_width = display_mode.w;
        window_height = display_mode.h;

        #endif

    	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_BORDERLESS);
        
        if(!window)
        {
            fprintf(stderr, "Error creating SDL Window\n");
            return false;
        }
        #ifndef __EMSCRIPTEN__

	    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	    #endif
        return true;
    }
}

void destroy_window(void)
{
    if (window)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }
}