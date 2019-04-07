#ifndef __SORT_H_INCLUDED__
#define __SORT_H_INCLUDED__

#include <SDL2/SDL.h>
#include <vector>

namespace sort
{
    void merge(std::vector<SDL_Rect> &array, int left, int middle, int right);
    void merge_sort(std::vector<SDL_Rect> &array, int left, int right);
    void render(std::vector<SDL_Rect> &array, int left, int right, int middle);
    void quick_sort(std::vector<SDL_Rect> &array, int low, int high);
    int partition(std::vector<SDL_Rect> &array, int low, int high);
}

#endif
