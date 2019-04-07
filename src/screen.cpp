#include "screen.hpp"

namespace screen
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    bool init()
    {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
	    printf("SDL could not initialize! SDL Error: %s\n",
		   SDL_GetError());
	    return false;
	} else {
	    //Set texture filtering to linear
	    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		printf("Warning: Linear texture filtering not enabled!");

	    window = SDL_CreateWindow("Sorting Algorithms Visualization",
				      SDL_WINDOWPOS_UNDEFINED,
				      SDL_WINDOWPOS_UNDEFINED,
				      WIDTH,
				      HEIGHT,
				      SDL_WINDOW_SHOWN);

	    if (window == nullptr) {
		printf("Window could not be created! SDL Error: %s\n",
		       SDL_GetError());
		return false;
	    } else {
		renderer = SDL_CreateRenderer(window,
					      -1,
					      SDL_RENDERER_ACCELERATED);

		if (renderer == nullptr) {
		    printf("Renderer could not be created! SDL Error: %s\n",
			   SDL_GetError());
		    return false;
		} else {
		    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		}
	    }
	}
	return true;
    }

    void close()
    {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;
	SDL_Quit();
    }

    void clear()
    {
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);
    }

    void finish(std::vector<SDL_Rect> &array)
    {
	for (size_t i = 0; i < array.size() - 1; i++) {
	    if (array[i].h <= array[i + 1].h) {
		SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderFillRect(renderer, &array[i]);
		SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderFillRect(renderer, &array[i + 1]);
	    }
	    SDL_RenderPresent(renderer);
	}
    }

    void show_array(std::vector<SDL_Rect> &array)
    {
	for (size_t i = 0; i < array.size() - 1; i++) {
	    SDL_SetRenderDrawColor(screen::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	    SDL_RenderFillRect(screen::renderer, &array[i]);
	    SDL_SetRenderDrawColor(screen::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	    SDL_RenderFillRect(screen::renderer, &array[i + 1]);
	    SDL_RenderPresent(screen::renderer);
	}
    }
}
