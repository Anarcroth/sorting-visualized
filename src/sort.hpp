#ifndef __SORT_H_INCLUDED__
#define __SORT_H_INCLUDED__

#include <SDL2/SDL.h>
#include <vector>

namespace sort
{
    // merge sort
    void merge(std::vector<SDL_Rect> &array, int left, int middle, int right);
    void merge_sort(std::vector<SDL_Rect> &array, int left, int right);
    void render_ms(std::vector<SDL_Rect> &array, int left, int right, int middle);

    // quick sort
    void quick_sort(std::vector<SDL_Rect> &array, int low, int high);
    int partition(std::vector<SDL_Rect> &array, int low, int high);

    // binary tree sort
    std::vector<SDL_Rect> binary_tree_sort(std::vector<SDL_Rect> &array);

    // heap sort
    void heap_sort(std::vector<SDL_Rect> &array);
    void heapify(std::vector<SDL_Rect> &array, int n, int i);

    // shell sort
    void shell_sort(std::vector<SDL_Rect> &array);

    //////////////////////////////////////////
    // Same algorithms, but using only ints // (don't question this horrific code, iz perfect)
    //////////////////////////////////////////
    // merge sort
    void merge(std::vector<int> &array, int left, int middle, int right);
    void merge_sort(std::vector<int> &array, int left, int right);

    // quick sort
    void quick_sort(std::vector<int> &array, int low, int high);
    int partition(std::vector<int> &array, int low, int high);

    // binary tree sort
    // std::vector<int> binary_tree_sort(std::vector<int> &array);

    // heap sort
    void heap_sort(std::vector<int> &array);
    void heapify(std::vector<int> &array, int n, int i);

    // shell sort
    void shell_sort(std::vector<int> &array);
}

#endif
