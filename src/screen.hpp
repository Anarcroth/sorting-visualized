#ifndef __SCREEN_H_INCLUDED__
#define __SCREEN_H_INCLUDED__

#include <SDL2/SDL.h>
#include <vector>

namespace screen
{
    bool init();

    void close();
    void clear();
    void finish(std::vector<SDL_Rect> &array);
    void show_array(std::vector<SDL_Rect> &array);

    inline constexpr int WIDTH = 1280;
    inline constexpr int HEIGHT = 800;

    extern SDL_Window* window;
    extern SDL_Renderer* renderer;
}

#endif
