#include <cmath>

#include "number_set.hpp"
#include "screen.hpp"

namespace number_set
{
    // Default values
    std::mt19937 rng {std::random_device()()};
    std::uniform_int_distribution<int> even_rand(0, screen::HEIGHT);
    int pillar_width = 1;
    int num_pillars = screen::WIDTH;
    int upper_bound = screen::HEIGHT;

    std::vector<SDL_Rect> gen(int num_set, int set_size)
    {
	// If needed, change default values.
	if (set_size > 1) {
	    num_pillars = set_size;
	    if (set_size <= screen::WIDTH) {
		pillar_width = screen::WIDTH / set_size;
	    } else {
		// if the set size is too big, extend the range of random numbers
		even_rand.param(std::uniform_int_distribution<int>::param_type(0, set_size));
		upper_bound = set_size;
	    }
	}

	switch(num_set) {
	case 0:
	    return random();
	case 1:
	    return seq_random();
	case 2:
	    return reversed();
	}
    }

    std::vector<SDL_Rect> random()
    {
	std::vector<SDL_Rect> pillars;
	for (int i = 0; i < num_pillars; i++) {
	    int pillar_val = even_rand(rng);
	    int rect_y = screen::HEIGHT - pillar_val;

	    SDL_Rect rect = {i * pillar_width, rect_y, pillar_width, pillar_val};

	    pillars.push_back(rect);
	}
	return pillars;
    }

    std::vector<SDL_Rect> seq_random()
    {
	std::vector<int> pillar_vals;
	for (int i = 0; i < num_pillars; i++) {
	    double frac = (double)upper_bound / num_pillars;
	    int pillar_val = std::floor(frac * i);
	    pillar_vals.push_back(pillar_val);
	}
	std::random_shuffle(pillar_vals.begin(), pillar_vals.end());
	std::vector<SDL_Rect> pillars;
	for (int i = 0; i < num_pillars; i++) {
	    int rect_y = screen::HEIGHT - pillar_vals[i];

	    SDL_Rect rect = {i * pillar_width, rect_y, pillar_width, pillar_vals[i]};

	    pillars.push_back(rect);
	}
	return pillars;
    }

    std::vector<SDL_Rect> reversed()
    {
	std::vector<SDL_Rect> pillars;
	for (int i = 0; i < num_pillars; i++) {
	    double frac = (double)upper_bound / num_pillars;
	    int pillar_val = std::floor(frac * (num_pillars - i));
	    int rect_y = screen::HEIGHT - pillar_val;

	    SDL_Rect rect = {i * pillar_width, rect_y, pillar_width, pillar_val};

	    pillars.push_back(rect);
	}
	return pillars;
    }
}
