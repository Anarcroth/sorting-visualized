#include "screen.hpp"

namespace screen
{
    void clear(SDL_Renderer* r)
    {
	SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(r);
    }
}
