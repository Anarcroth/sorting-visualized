#ifndef __NUMBER_SET_H_INCLUDED__
#define __NUMBER_SET_H_INCLUDED__

#include <random>
#include <algorithm>
#include <vector>

#include <SDL2/SDL.h>

namespace number_set
{
    int gen();
    std::vector<SDL_Rect> random();
    std::vector<SDL_Rect> seq_random();
    //std::vector<SDL_Rect> nearly_sorted();
    std::vector<SDL_Rect> reversed();
    //std::vector<SDL_Rect> few_unique();

    extern std::mt19937 rng;
    extern std::uniform_int_distribution<int> even_rand;
}

#endif
