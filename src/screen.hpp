#ifndef __SCREEN_H_INCLUDED__
#define __SCREEN_H_INCLUDED__

#include <SDL2/SDL.h>
#include <vector>

namespace screen
{
    void clear(SDL_Renderer* r);
    void finish(SDL_Renderer* r, std::vector<SDL_Rect> &array);
}

#endif
