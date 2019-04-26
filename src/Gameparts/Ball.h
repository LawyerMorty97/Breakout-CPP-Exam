//
// Created by Mathias Berntsen on 25/04/2019.
//

#ifndef BREAKOUT_EXAM_BALL_H
#define BREAKOUT_EXAM_BALL_H

#include "../Components/Screen.h"
#include "../Components/Image.h"
#include "../Components/IPosition.h"
#include "../Components/IGame.h"
#include "../Managers/ImageManager.h"

#include "SDL.h"

class Ball : public IPosition, public IGame {
public:
    float radius;
    bool stuck;
    vec2 vel;

    Ball(vec2 position, float radius, vec2 velocity);

    void Move(float deltaTime);
    void Draw();
private:
    int max_w, max_h;
    Image* txd;
};


#endif //BREAKOUT_EXAM_BALL_H
