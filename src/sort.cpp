#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

#include "sort.hpp"
#include "screen.hpp"
#include "binary_tree.hpp"

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
	    render_ms(array, left, right, middle);
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
	render_ms(array, left, array.size(), middle);
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

    void render_ms(std::vector<SDL_Rect> &array, int left, int right, int middle)
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

    std::vector<SDL_Rect> binary_tree_sort(std::vector<SDL_Rect> &array)
    {
	binary_tree bt;
	for (auto& a : array) {
	    bt.insert(a);
	}
	bt.in_order_traversal();
	return bt.pillars;
    }

    void heap_sort(std::vector<SDL_Rect> &array)
    {
	for (int i = array.size() / 2 - 1; i >= 0; i--)
	    heapify(array, array.size(), i);

	for (int i = array.size() - 1; i >= 0; i--) {
	    std::swap(array[0], array[i]);
	    heapify(array, i, 0);
	}
    }

    void heapify(std::vector<SDL_Rect> &array, int n, int i)
    {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	screen::clear();
	for (size_t i = 0; i < array.size(); i++) {
	    array[i].x = i * array[i].w;
	    SDL_SetRenderDrawColor(screen::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	    SDL_RenderFillRect(screen::renderer, &array[i]);
	}

	if (l < n && array[l].h > array[largest].h)
	    largest = l;

	if (r < n && array[r].h > array[largest].h)
	    largest = r;

	SDL_SetRenderDrawColor(screen::renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(screen::renderer, &array[i]);

	SDL_SetRenderDrawColor(screen::renderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderFillRect(screen::renderer, &array[largest]);
	SDL_RenderPresent(screen::renderer);

	if (largest != i) {
	    std::swap(array[i], array[largest]);
	    heapify(array, n, largest);
	}
    }

    void shell_sort(std::vector<SDL_Rect> &array)
    {
	for (int gap = array.size() / 2; gap > 0; gap /= 2)
	{
	    for (int i = gap; i < array.size(); i += 1)
	    {
		auto temp_pillr = array[i];
		int j;
		for (j = i; j >= gap && array[j - gap].h > temp_pillr.h; j -= gap)
		    array[j] = array[j - gap];

		array[j] = temp_pillr;

		screen::clear();
		for (size_t i = 0; i < array.size(); i++) {
		    array[i].x = i * array[i].w;
		    SDL_SetRenderDrawColor(screen::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		    SDL_RenderFillRect(screen::renderer, &array[i]);
		}
		SDL_SetRenderDrawColor(screen::renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(screen::renderer, &array[j]);
		SDL_SetRenderDrawColor(screen::renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(screen::renderer, &array[i]);
		SDL_RenderPresent(screen::renderer);
	    }
	}
    }

    void merge(std::vector<int> &array, int left, int middle, int right)
    {
	int i, j, k;
	int n1 = middle - left + 1;
	int n2 = right - middle;

	std::vector<int> L(n1), R(n2);

	for (i = 0; i < n1; i++)
	    L[i] = array[left + i];

	for (j = 0; j < n2; j++)
	    R[j] = array[middle + 1 + j];

	i = 0;
	j = 0;
	k = left;

	while (i < n1 && j < n2) {
	    if (L[i] <= R[j]) {
		array[k] = L[i];
		i++;
	    } else {
		array[k] = R[j];
		j++;
	    }
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
    }

    void merge_sort(std::vector<int> &array, int left, int right)
    {
	if (left < right) {
	    int middle = left + (right - left) / 2;

	    merge_sort(array, left, middle);
	    merge_sort(array, middle + 1, right);

	    merge(array, left, middle, right);
	}
    }

    void quick_sort(std::vector<int> &array, int low, int high)
    {
	if (high > low)
	{
	    int pivot = partition(array, low, high);
	    quick_sort(array, low, pivot - 1);
	    quick_sort(array, pivot + 1, high);
	}
    }

    int partition(std::vector<int> &array, int low, int high)
    {
	int pivot = array[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) {
	    if (array[j] <= pivot) {
		i++;
		std::swap(array[i], array[j]);
	    }
	}

	std::swap(array[i + 1], array[high]);

	return i + 1;
    }

    // std::vector<int> binary_tree_sort(std::vector<int> &array)
    // {
    // 	binary_tree bt;
    // 	for (auto& a : array) {
    // 	    bt.insert(a);
    // 	}
    // 	bt.in_order_traversal();
    // 	return bt.pillars;
    // }

    void heap_sort(std::vector<int> &array)
    {
	for (int i = array.size() / 2 - 1; i >= 0; i--)
	    heapify(array, array.size(), i);

	for (int i = array.size() - 1; i >= 0; i--) {
	    std::swap(array[0], array[i]);
	    heapify(array, i, 0);
	}
    }

    void heapify(std::vector<int> &array, int n, int i)
    {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && array[l] > array[largest])
	    largest = l;

	if (r < n && array[r] > array[largest])
	    largest = r;

	if (largest != i) {
	    std::swap(array[i], array[largest]);
	    heapify(array, n, largest);
	}
    }

    void shell_sort(std::vector<int> &array)
    {
	for (int gap = array.size() / 2; gap > 0; gap /= 2)
	{
	    for (int i = gap; i < array.size(); i += 1)
	    {
		int temp = array[i];
		int j;
		for (j = i; j >= gap && array[j - gap] > temp; j -= gap)
		    array[j] = array[j - gap];

		array[j] = temp;
	    }
	}
    }
}
