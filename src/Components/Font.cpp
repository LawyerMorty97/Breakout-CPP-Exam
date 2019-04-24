//
// Created by Mathias Berntsen on 24/04/2019.
//

#include "Font.h"

Font::Font(const char* font, int size) : Size(size) {
    this->size = size;
    this->font = TTF_OpenFont(font, size);
}

Font::~Font() {
    TTF_CloseFont(font);
}

SDL_Texture* Font::CreateText(const char *text, SDL_Color color) {

    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    return texture;
}

void Font::FreeText(SDL_Texture* texture) {
    SDL_DestroyTexture(texture);
}

void Font::DrawText(SDL_Texture *texture) {
    int w, h = 0;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect dsrect = {0, 0, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &dsrect);
}