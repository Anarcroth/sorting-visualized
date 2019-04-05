#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

#include "sort.hpp"
#include "screen.hpp"

namespace sort
{
    void merge(SDL_Renderer* r, std::vector<SDL_Rect> &array, int left, int middle, int right)
    {
	screen::clear(r);

	render(r, array, left, right, middle);
	int i, j, k;
	int n1 = middle - left + 1;
	int n2 = right - middle;

	std::vector<SDL_Rect> L(n1), R(n2);

	for (i = 0; i < n1; i++)
	    L[i] = array[left + i];

	for (j = 0; j < n2; j++)
	    R[j] = array[middle + 1 + j];

	i = 0;
	j = 0;
	k = left;

	while (i < n1 && j < n2) {
	    render(r, array, left, right, middle);
	    SDL_SetRenderDrawColor(r, 0xFF, 0x00, 0x00, 0xFF);
	    SDL_RenderFillRect(r, &L[i]);
	    SDL_RenderFillRect(r, &R[j]);

	    if (L[i].h <= R[j].h) {
		array[k] = L[i];
		i++;
	    } else {
		array[k] = R[j];
		j++;
	    }
	    SDL_RenderPresent(r);
	    k++;
	    int a = std::cin.get();
	}

	while (i < n1) {
	    array[k] = L[i];
	    render(r, array, left, right, middle);
	    i++;
	    k++;
	}

	while (j < n2) {
	    array[k] = R[j];
	    render(r, array, left, right, middle);
	    j++;
	    k++;
	}
    }

    void merge_sort(SDL_Renderer* r, std::vector<SDL_Rect> &array, int left, int right)
    {
	if (left < right) {
	    int middle = left + (right - left) / 2;

	    merge_sort(r, array, left, middle);
	    merge_sort(r, array, middle + 1, right);

	    merge(r, array, left, middle, right);
	}
    }

    void render(SDL_Renderer* r, std::vector<SDL_Rect> &array, int left, int right, int middle)
    {
	SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(r);



	for (size_t i = 0; i < array.size(); i++) {
	    array[i].x = i * (1 + 15);
	    SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
	    SDL_RenderFillRect(r, &array[i]);
	}

		// Show the left, right, middle pivots
	SDL_SetRenderDrawColor(r, 0x00, 0xFF, 0xFF, 0x00);
	SDL_RenderFillRect(r, &array[middle]);

	SDL_SetRenderDrawColor(r, 0x00, 0xFF, 0x00, 0x00);
	SDL_RenderFillRect(r, &array[left]);

	SDL_SetRenderDrawColor(r, 0x00, 0xFF, 0x00, 0x00);
	SDL_RenderFillRect(r, &array[right]);

	SDL_RenderPresent(r);
	// stop the showing

	SDL_RenderPresent(r);
    }
}
