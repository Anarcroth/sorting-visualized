#ifndef __SORT_H_INCLUDED__
#define __SORT_H_INCLUDED__

#include <SDL2/SDL.h>
#include <vector>

namespace sort
{
    void merge(SDL_Renderer* r, std::vector<SDL_Rect> &array, int left, int middle, int right);
    void merge_sort(SDL_Renderer* r, std::vector<SDL_Rect> &array, int left, int right);
    void render(SDL_Renderer* r, std::vector<SDL_Rect> &array, int left, int right, int middle);
}

#endif
