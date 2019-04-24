//
// Created by Mathias Berntsen on 24/04/2019.
//

#include "Text.h"

void Text::updateText() {
    surface = TTF_RenderText_Solid(font->font, text, color);
    texture = CreateTexture(surface);
    SDL_FreeSurface(surface);

    std::pair<int, int> tsize = GetTextureSize(texture);
    setSize(Set, tsize.first, tsize.second);
}

Text::Text(Font* font, const char* text) {
    this->font = font;
    this->text = const_cast<char*>(text);
    color = {255, 255, 255};

    SDL_Window* window = GetWindow();
    renderer = GetRenderer();

    updateText();
}

void Text::setText(char *text) {
    SDL_DestroyTexture(texture);
    this->text = text;

    updateText();
}

void Text::setColor(Uint8 r, Uint8 g, Uint8 b) {
    color = {r, g, b};

    updateText();
}

Text::~Text() {
    SDL_DestroyTexture(texture);
}

void Text::Draw() {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}