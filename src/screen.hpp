#ifndef __SCREEN_H_INCLUDED__
#define __SCREEN_H_INCLUDED__

#include <SDL2/SDL.h>

namespace screen
{
    void clear(SDL_Renderer* r);
    //void render(SDL_Renderer* r, std::vector<SDL_Rect> &array, int left);
}

#endif
