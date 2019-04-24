//
// Created by Mathias Berntsen on 24/04/2019.
//

#ifndef C_EXAM_FONT_H
#define C_EXAM_FONT_H

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class Font {
public:
    Font(const char* font, int size);
    ~Font();

    TTF_Font* font;
    const int &Size;

    SDL_Texture* CreateText(const char* text, SDL_Color color);
    void FreeText(SDL_Texture* texture);
    void DrawText(SDL_Texture* texture);
private:
    SDL_Renderer* renderer;

    int size;

    SDL_Surface* surface;
    SDL_Texture* texture;
};


#endif //C_EXAM_FONT_H
