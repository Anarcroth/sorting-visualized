#include <thread>
#include <chrono>
#include "screen.hpp"

namespace screen
{
    void clear(SDL_Renderer* r)
    {
	SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(r);
    }

    void finish(SDL_Renderer* r, std::vector<SDL_Rect> &array)
    {
	for (size_t i = 0; i < array.size(); i++) {
	    SDL_SetRenderDrawColor(r, 0x00, 0xFF, 0x00, 0xFF);
	    SDL_RenderFillRect(r, &array[i]);
	    SDL_RenderPresent(r);
	    std::this_thread::sleep_for(std::chrono::milliseconds(05));
	}
    }
}
