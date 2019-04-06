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
	    render(r, array, left, right, middle);
	    SDL_SetRenderDrawColor(r, 0xFF, 0x00, 0x00, 0xFF);
	    SDL_RenderFillRect(r, &array[k]);
	    SDL_RenderPresent(r);

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
	render(r, array, left, array.size(), middle);
	SDL_RenderPresent(r);
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
	screen::clear(r);

	for (size_t i = 0; i < array.size(); i++) {
	    array[i].x = i * array[i].w;
	    SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
	    SDL_RenderFillRect(r, &array[i]);
	}

	// Show the left, right, and middle pivots
	SDL_SetRenderDrawColor(r, 0x00, 0xFF, 0xFF, 0x00);
	SDL_RenderFillRect(r, &array[middle]);

	SDL_SetRenderDrawColor(r, 0x00, 0xFF, 0x00, 0x00);
	SDL_RenderFillRect(r, &array[left]);
    }

    void quick_sort(SDL_Renderer* r, std::vector<SDL_Rect> &array, int low, int high)
    {
	if (high > low)
	{
	    int pivot = partition(r, array, low, high);
	    quick_sort(r, array, low, pivot - 1);
	    quick_sort(r, array, pivot + 1, high);
	}
    }

    int partition(SDL_Renderer* r, std::vector<SDL_Rect> &array, int low, int high)
    {
	screen::clear(r);

	int pivot = array[high].h;
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) {
	    if (array[j].h <= pivot) {
		i++;
		std::swap(array[i], array[j]);
	    }

	    screen::clear(r);
	    for (size_t i = 0; i < array.size(); i++) {
		array[i].x = i * array[i].w;
		SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(r, &array[i]);
	    }

	    SDL_SetRenderDrawColor(r, 0xFF, 0x00, 0x00, 0xFF);
	    SDL_RenderFillRect(r, &array[j]);
	    SDL_RenderFillRect(r, &array[i]);

	    SDL_SetRenderDrawColor(r, 0x00, 0xFF, 0x00, 0xFF);
	    SDL_RenderFillRect(r, &array[low]);
	    SDL_RenderFillRect(r, &array[high]);

	    SDL_RenderPresent(r);
	}

	std::swap(array[i + 1], array[high]);

	screen::clear(r);
	for (size_t i = 0; i < array.size(); i++) {
	    array[i].x = i * array[i].w;
	    SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
	    SDL_RenderFillRect(r, &array[i]);
	}

	SDL_SetRenderDrawColor(r, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(r, &array[i]);

	SDL_SetRenderDrawColor(r, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderFillRect(r, &array[low]);
	SDL_RenderFillRect(r, &array[high]);
	SDL_RenderPresent(r);

	return i + 1;
    }
}
