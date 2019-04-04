#include "sort.hpp"

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

    void merge_sort(std::vector<SDL_Rect> &array, int left, int right)
    {
	if (left < right) {
	    int middle = left + (right - left) / 2;

	    merge_sort(array, left, middle);
	    merge_sort(array, middle + 1, right);

	    merge(array, left, middle, right);
	}
    }
}
