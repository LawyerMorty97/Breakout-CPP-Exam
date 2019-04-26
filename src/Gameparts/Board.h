//
// Created by Mathias Berntsen on 25/04/2019.
//

#ifndef BREAKOUT_EXAM_BOARD_H
#define BREAKOUT_EXAM_BOARD_H

#include <math.h>

#include "../Components/IGame.h"
#include "../Components/IPosition.h"
#include "../Components/IComponent.h"

#include "../Components/Font.h"
#include "../Components/Text.h"

#include "../Gameparts/Ball.h"
#include "../Gameparts/Brick.h"

class Board : public IGame, public IComponent, public IPosition {
public:
    Board();
    ~Board();

    void Update(float deltaTime);
    void Draw(float deltaTime);

protected:
    bool IsCursorInArea();
    bool CheckCollisions(IPosition rect);
private:
    InputManager* input;
    ImageManager* imageManager;
    Screen* screen;
    GameManager* game;

    std::vector<Brick*> bricks;

    Font* font;

    Image* board;
    Ball* ball;
};


#endif //BREAKOUT_EXAM_BOARD_H
