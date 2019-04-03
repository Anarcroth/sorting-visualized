#include <SDL2/SDL.h>
#include <vector>

namespace sort
{
    void merge(std::vector<SDL_Rect> &array, int left, int middle, int right)
    {
	int i, j, k;
	int n1 = middle - left + 1;
	int n2 = right - middle;

	std::vector<SDL_Rect> L(n1), R(n2);

	for (i = 0; i < n1; i++)
	    L[i].h = array[left + i].h;

	for (j = 0; j < n2; j++)
	    R[j].h = array[middle + 1 + j].h;

	i = 0;
	j = 0;
	k = left;

	while (i < n1 && j < n2) {
	    if (L[i].h <= R[j].h) {
		array[k].h = L[i].h;
		i++;
	    } else {
		array[k].h = R[j].h;
		j++;
	    }
	    k++;
	}

	while (i < n1) {
	    array[k].h = L[i].h;
	    i++;
	    k++;
	}

	while (j < n2) {
	    array[k].h = R[j].h;
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
