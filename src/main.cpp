#include <random>
#include <vector>

#include "sort.hpp"
#include "screen.hpp"
#include "number_set.hpp"

int main(int argc, char* args[])
{
    // TODO
    // Separate random gen into another function or even file
    // Parse arguments
    // Add timer
    // Add statistics output
    std::mt19937 rng {std::random_device()() };
    std::uniform_int_distribution<int> even_rand(0, screen::HEIGHT);
    int pillar_width = 1;
    int num_pillars = screen::WIDTH / pillar_width;
    std::vector<SDL_Rect> pillars;
    for (int i = 0; i < num_pillars; i++) {
	int pillar_val = even_rand(rng);
	int rect_y = screen::HEIGHT - pillar_val;
	SDL_Rect rect = {i * pillar_width, rect_y, pillar_width, pillar_val};
	pillars.push_back(rect);
    }

    if (!screen::init()) {
	printf("Failed to initialize!\n");
    } else {
	while (!screen::quit) {
	    screen::handle_event();
	    screen::clear(screen::renderer);
	    sort::merge_sort(screen::renderer, pillars, 0, num_pillars);
	    screen::finish(screen::renderer, pillars);
	    screen::quit = true;
	}
    }

    screen::close();
    return 0;
}
