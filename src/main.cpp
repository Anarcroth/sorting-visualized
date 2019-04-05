#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <cmath>
#include <random>
#include <vector>
#include <thread>
#include <chrono>

#include "sort.hpp"
#include "screen.hpp"

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
    std::mt19937 rng {std::random_device()() };
    std::uniform_int_distribution<int> even_rand(0, SCREEN_HEIGHT);
    int pillar_width = 1;
    int num_pillars = SCREEN_WIDTH / pillar_width;
    std::vector<SDL_Rect> pillars;
    for (int i = 0; i < num_pillars; i++) {
	int pillar_val = even_rand(rng);
	int rect_y = SCREEN_HEIGHT - pillar_val;
	SDL_Rect rect = {i * ( pillar_width), rect_y, pillar_width, pillar_val};
	pillars.push_back(rect);
    }

    if (!init()) {
	printf("Failed to initialize!\n");
    } else {
	bool quit = false;

	SDL_Event e;

	while (!quit) {

	    if (SDL_WaitEvent(&e)) {
		if (e.type == SDL_QUIT)
		    quit = true;
		else if (e.type == SDL_KEYDOWN) {
		    switch (e.key.keysym.sym) {
		    case SDLK_q: quit = true;
			break;
		    }
		}
	    }
	    screen::clear(renderer);

	    sort::merge_sort(renderer, pillars, 0, num_pillars);
	    exit(0);
	    //Update screen
	    //SDL_RenderPresent(renderer);
	}
    }

    close();
    return 0;
}
