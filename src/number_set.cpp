#include <cmath>

#include "number_set.hpp"
#include "screen.hpp"

namespace number_set
{
    std::mt19937 rng {std::random_device()()};
    std::uniform_int_distribution<int> even_rand(0, screen::HEIGHT);

    int gen()
    {
	return even_rand(rng);
    }

    std::vector<SDL_Rect> random()
    {
	int pillar_width = 1;
	int num_pillars = screen::WIDTH / pillar_width;

	std::vector<SDL_Rect> pillars;
	for (int i = 0; i < num_pillars; i++) {
	    int pillar_val = even_rand(rng);
	    int rect_y = screen::HEIGHT - pillar_val;

	    SDL_Rect rect = {i * pillar_width, rect_y, pillar_width, pillar_val};

	    pillars.push_back(rect);
	}
	return pillars;
    }

    std::vector<SDL_Rect> reversed()
    {
	int pillar_width = 1;
	int num_pillars = screen::WIDTH / pillar_width;

	std::vector<SDL_Rect> pillars;
	for (int i = 0; i < num_pillars; i++) {
	    double frac = (double)screen::HEIGHT / screen::WIDTH;
	    int pillar_val = std::floor((frac) * (num_pillars - i));
	    int rect_y = screen::HEIGHT - pillar_val;

	    SDL_Rect rect = {i * pillar_width, rect_y, pillar_width, pillar_val};

	    pillars.push_back(rect);
	}
	return pillars;
    }
}
