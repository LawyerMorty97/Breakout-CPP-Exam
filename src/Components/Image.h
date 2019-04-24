//
// Created by Mathias Berntsen on 18/02/2019.
//

#ifndef C_ARBEIDSKRAV_IMAGE_H
#define C_ARBEIDSKRAV_IMAGE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <tuple>

#include "IComponent.h"
#include "IPosition.h"
#include "../Utils.h"

class Image : public IComponent, public IPosition {
public:
    SDL_Surface* surface;
    SDL_Texture* texture;

    Image(std::string filename, int x, int y, int w, int h);
    ~Image();

    std::string filename;

    bool Draw();

    std::pair<int, int> GetSurfaceSize();

    void setColor(int r, int g, int b, int a = 255);
    std::tuple<int, int, int, int> getColor();

    void setViewable(bool toggle);
    bool isViewable();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool m_CanRender = false;
    bool m_viewable = true;
};


#endif //C_ARBEIDSKRAV_IMAGE_H
