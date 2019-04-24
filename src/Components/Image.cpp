//
// Created by Mathias Berntsen on 18/02/2019.
//

#include "Image.h"

Image::Image(std::string filename, int x, int y, int w, int h) {
    //window = SDL_GL_GetCurrentWindow();
    //renderer = SDL_GetRenderer(window);
    window = GetWindow();
    renderer = GetRenderer();

    //surface = SDL_LoadBMP(Utils::stringToChar("images/" + filename));
    std::string file = "content/images/" + filename;
    surface = IMG_Load(file.c_str());

    if (surface == nullptr) {
        Utils::error_sdl("Failed to load image '" + filename + "' (" + IMG_GetError() + ".");
        return;
    }

    texture = CreateTexture(surface);
    setPosition(Set, x, y);
    setSize(Set, w, h);
    //SDL_FreeSurface(surface);

    m_CanRender = true;
}

void Image::setViewable(bool toggle) {
    m_viewable = toggle;
}

bool Image::isViewable() {
    return m_CanRender ? m_viewable : false;
}

std::pair<int, int> Image::GetSurfaceSize() {
    return {surface->w, surface->h};
}

std::tuple<int, int, int, int> Image::getColor() {
    Uint8 r, g, b, a;

    SDL_GetTextureColorMod(texture, &r, &g, &b);
    SDL_GetTextureAlphaMod(texture, &a);

    return {r, g, b, a};
}

void Image::setColor(int r, int g, int b, int a) {
    SDL_SetTextureColorMod(texture, r, g, b);
    SDL_SetTextureAlphaMod(texture, a);
}

bool Image::Draw() {
    if (!m_CanRender || !m_viewable)
        return false;

    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    return true;
}

Image::~Image() {
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}