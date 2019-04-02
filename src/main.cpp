#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <cmath>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;

bool init();
void close();

SDL_Window* window = nullptr;
SDL_Renderer* renderer  = nullptr;

bool init()
{
    if (SDL_Init( SDL_INIT_VIDEO) < 0) {
	printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	return false;
    } else {
	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	    printf( "Warning: Linear texture filtering not enabled!");

	window = SDL_CreateWindow("Sorting Algorithms Visualization",
				   SDL_WINDOWPOS_UNDEFINED,
				   SDL_WINDOWPOS_UNDEFINED,
				   SCREEN_WIDTH,
				   SCREEN_HEIGHT,
				   SDL_WINDOW_SHOWN);
	if (window == nullptr) {
	    printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	    return false;
	} else {
	    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	    if (renderer == nullptr) {
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
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

int main(int argc, char* args[])
{
    if (!init()) {
	printf("Failed to initialize!\n");
    } else {
	bool quit = false;

	SDL_Event e;

	while(!quit) {

	    while(SDL_PollEvent(&e) != 0)
		if(e.type == SDL_QUIT)
		    quit = true;

	    //Clear screen
	    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	    SDL_RenderClear(renderer);

	    //Render red filled quad
	    SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	    SDL_RenderFillRect(renderer, &fillRect);

	    //Render green outlined quad
	    SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
	    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
	    SDL_RenderDrawRect(renderer, &outlineRect);

	    //Draw blue horizontal line
	    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
	    SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

	    //Draw vertical line of yellow dots
	    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
	    for(int i = 0; i < SCREEN_HEIGHT; i += 4)
	    {
		SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, i);
	    }

	    //Update screen
	    SDL_RenderPresent(renderer);
	}
    }

    close();
    return 0;
}
