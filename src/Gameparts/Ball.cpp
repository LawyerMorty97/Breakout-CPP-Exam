//
// Created by Mathias Berntsen on 25/04/2019.
//

#include "Ball.h"

Ball::Ball(vec2 position, float radius, vec2 velocity) {
    setPosition(Set, position);
    setSize(Set, 16, 16);

    txd = ImageManager::instance()->Add("ball", "ball.png", position.x, position.y, getSize().x, getSize().y);
    max_w = 1280 - 310;
    max_h = 720;
    vel = velocity;
    this->radius = radius;

    stuck = true;
}

void Ball::Draw() {
    txd->Draw();
}

void Ball::Move(float deltaTime) {
    if (!stuck) {
        setPosition(Modify, vel.x * deltaTime, vel.y * deltaTime);

        if (rect.x <= 0) {
            vel.x = -vel.x;
            rect.x = 0;
        }
        else if (rect.x + rect.w >= max_w) {
            vel.x = -vel.x;
            rect.x = max_w - rect.w;
        }

        if (rect.y <= 0) {
            vel.y = -vel.y;
            rect.y = 0;
        }
        else if (rect.y + rect.w >= max_h) {
            GetGame()->UpdateLives();
            vel.y = -vel.y;
            rect.y = max_h - rect.h;
        }
    }
    txd->setPosition(Set, vec2(rect.x, rect.y));
}