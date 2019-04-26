//
// Created by Mathias Berntsen on 24/04/2019.
//

#ifndef C_EXAM_TEXT_H
#define C_EXAM_TEXT_H

#include <tuple>

#include "Font.h"
#include "../Utils.h"

#include "IPosition.h"
#include "IComponent.h"

class Text : public IComponent, public IPosition {
public:
    Text(Font* font, const char* text);
    ~Text();

    void setColor(Uint8 r, Uint8 g, Uint8 b);
    void setText(const char* text);

    void Draw();
private:
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    Font* font;

    void updateText();

    char* text;
    SDL_Color color;
};


#endif //C_EXAM_TEXT_H
