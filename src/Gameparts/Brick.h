//
// Created by Mathias Berntsen on 25/04/2019.
//

#ifndef BREAKOUT_EXAM_BRICK_H
#define BREAKOUT_EXAM_BRICK_H

#include <stdlib.h>
#include "../Components/Image.h"

#include "../Components/IPosition.h"
#include "../Managers/ImageManager.h"

class Brick : public IPosition {
public:
    enum BrickType {
        Normal = 0,
        Hard = 1,
        Obstacle = 2
    };

    struct brick_t {
        Image* image;
        BrickType type;
        bool strong;
    };

    Brick(BrickType type, int x, int y);
    ~Brick();

    BrickType GetType();

    bool IsHit();
    void Hit();
    void SetColor(int r, int g, int b);
private:
    brick_t m_brick;

    bool isHit = false;
};

#endif //BREAKOUT_EXAM_BRICK_H
