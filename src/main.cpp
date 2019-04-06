#include <random>
#include <vector>

#include "sort.hpp"
#include "screen.hpp"
#include "number_set.hpp"

int main(int argc, char* args[])
{
    // TODO
    // Parse arguments
    // Add timer
    // Add statistics output
    std::vector<SDL_Rect> pillars = number_set::reversed();

    if (!screen::init()) {
	printf("Failed to initialize!\n");
    } else {
	while (!screen::quit) {
	    screen::handle_event();
	    screen::clear(screen::renderer);
	    sort::merge_sort(screen::renderer, pillars, 0, pillars.size());
	    screen::finish(screen::renderer, pillars);
	    screen::quit = true;
	}
    }
    screen::close();
    return 0;
}
