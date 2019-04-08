#include <cmath>

#include "number_set.hpp"
#include "screen.hpp"

namespace number_set
{
    // Default values
    std::mt19937 rng {std::random_device()()};
    std::uniform_int_distribution<int> even_rand(0, screen::HEIGHT);
    int pillar_width = 1;
    int num_pillars = 1280; // yeah this is a magic number, it's 4 am

    std::vector<SDL_Rect> gen(int num_set, int set_size)
    {
	// If the number set size is below 1,
	// then take the screen height by default
	// and keep the default pillar width.
	if (set_size > 0) {
	    even_rand.param(
		std::uniform_int_distribution<int>::param_type(0, set_size));
	    pillar_width = set_size;
	}
	num_pillars = get_num_pillars();

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
	    double frac = (double)screen::HEIGHT / screen::WIDTH;
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
	    double frac = (double)screen::HEIGHT / screen::WIDTH;
	    int pillar_val = std::floor(frac * (num_pillars - i));
	    int rect_y = screen::HEIGHT - pillar_val;

	    SDL_Rect rect = {i * pillar_width, rect_y, pillar_width, pillar_val};

	    pillars.push_back(rect);
	}
	return pillars;
    }

    int get_num_pillars()
    {
	if (screen::WIDTH < pillar_width)
	    return pillar_width;
	else
	    return screen::WIDTH / pillar_width;
    }
}
