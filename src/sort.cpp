#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

#include "sort.hpp"
#include "screen.hpp"

namespace sort
{
    void merge(std::vector<SDL_Rect> &array, int left, int middle, int right)
    {
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
	    if (L[i].h <= R[j].h) {
		array[k] = L[i];
		i++;
	    } else {
		array[k] = R[j];
		j++;
	    }

            // Render the array and the different pivots
	    render(array, left, right, middle);
	    SDL_SetRenderDrawColor(screen::renderer, 0xFF, 0x00, 0x00, 0xFF);
	    SDL_RenderFillRect(screen::renderer, &array[k]);
	    SDL_RenderPresent(screen::renderer);

	    k++;
	}

	while (i < n1) {
	    array[k] = L[i];
	    i++;
	    k++;
	}

	while (j < n2) {
	    array[k] = R[j];
	    j++;
	    k++;
	}
	render(array, left, array.size(), middle);
	SDL_RenderPresent(screen::renderer);
    }

    void merge_sort(std::vector<SDL_Rect> &array, int left, int right)
    {
	if (left < right) {
	    int middle = left + (right - left) / 2;

	    merge_sort(array, left, middle);
	    merge_sort(array, middle + 1, right);

	    merge(array, left, middle, right);
	}
    }

    void render(std::vector<SDL_Rect> &array, int left, int right, int middle)
    {
	screen::clear();
	for (size_t i = 0; i < array.size(); i++) {
	    array[i].x = i * array[i].w;
	    SDL_SetRenderDrawColor(screen::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	    SDL_RenderFillRect(screen::renderer, &array[i]);
	}

	// Show the left and middle pivots
	SDL_SetRenderDrawColor(screen::renderer, 0x00, 0xFF, 0xFF, 0x00);
	SDL_RenderFillRect(screen::renderer, &array[middle]);

	SDL_SetRenderDrawColor(screen::renderer, 0x00, 0xFF, 0x00, 0x00);
	SDL_RenderFillRect(screen::renderer, &array[left]);
    }

    void quick_sort(std::vector<SDL_Rect> &array, int low, int high)
    {
	if (high > low)
	{
	    int pivot = partition(array, low, high);
	    quick_sort(array, low, pivot - 1);
	    quick_sort(array, pivot + 1, high);
	}
    }

    int partition(std::vector<SDL_Rect> &array, int low, int high)
    {
	screen::clear();

	int pivot = array[high].h;
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) {
	    if (array[j].h <= pivot) {
		i++;
		std::swap(array[i], array[j]);
	    }

	    screen::clear();
	    for (size_t i = 0; i < array.size(); i++) {
		array[i].x = i * array[i].w;
		SDL_SetRenderDrawColor(screen::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(screen::renderer, &array[i]);
	    }

	    SDL_SetRenderDrawColor(screen::renderer, 0xFF, 0x00, 0x00, 0xFF);
	    SDL_RenderFillRect(screen::renderer, &array[j]);
	    SDL_RenderFillRect(screen::renderer, &array[i]);

	    SDL_SetRenderDrawColor(screen::renderer, 0x00, 0xFF, 0x00, 0xFF);
	    SDL_RenderFillRect(screen::renderer, &array[low]);
	    SDL_RenderFillRect(screen::renderer, &array[high]);

	    SDL_RenderPresent(screen::renderer);
	}

	std::swap(array[i + 1], array[high]);

	screen::clear();
	for (size_t i = 0; i < array.size(); i++) {
	    array[i].x = i * array[i].w;
	    SDL_SetRenderDrawColor(screen::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	    SDL_RenderFillRect(screen::renderer, &array[i]);
	}

	SDL_SetRenderDrawColor(screen::renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(screen::renderer, &array[i]);

	SDL_SetRenderDrawColor(screen::renderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderFillRect(screen::renderer, &array[low]);
	SDL_RenderFillRect(screen::renderer, &array[high]);
	SDL_RenderPresent(screen::renderer);

	return i + 1;
    }
}
