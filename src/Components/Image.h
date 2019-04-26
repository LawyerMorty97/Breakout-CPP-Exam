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

    Image(std::string filename, float x, float y, float w, float h);
    ~Image();

    std::string filename;

    void ChangeImage(std::string name);
    bool Draw();

    std::pair<float, float> GetSurfaceSize();

    void setColor(float r, float g, float b, float a = 255);
    std::tuple<float, float, float, float> getColor();

    void setViewable(bool toggle);
    bool isViewable();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool m_CanRender = false;
    bool m_viewable = true;
};


#endif //C_ARBEIDSKRAV_IMAGE_H
