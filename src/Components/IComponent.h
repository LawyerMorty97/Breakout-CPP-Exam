//
// Created by Mathias Berntsen on 24/04/2019.
//

#ifndef C_EXAM_ICOMPONENT_H
#define C_EXAM_ICOMPONENT_H

#include <SDL.h>
#include <iostream>
#include <tuple>

class IComponent {
public:
    SDL_Window* GetWindow() {
        if (window == NULL)
            window = SDL_GL_GetCurrentWindow();

        return window;
    }

    SDL_Renderer* GetRenderer() {
        if (renderer == NULL)
            renderer = SDL_GetRenderer(window);

        return renderer;
    }

    SDL_Surface* GetScreenSurface() {
        return SDL_GetWindowSurface(window);
    }

    SDL_Texture* CreateTexture(SDL_Surface* surface) {
        return SDL_CreateTextureFromSurface(renderer, surface);
    }

    std::pair<int, int> GetTextureSize(SDL_Texture* texture) {
        int w, h;
        SDL_QueryTexture(texture, NULL, NULL, &w, &h);

        return {w, h};
    }
protected:
    SDL_Renderer* renderer = NULL;
    SDL_Window* window = NULL;
};

#endif //C_EXAM_ICOMPONENT_H
