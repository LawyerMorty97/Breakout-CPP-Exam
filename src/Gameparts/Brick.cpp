//
// Created by Mathias Berntsen on 25/04/2019.
//

#include "Brick.h"

Brick::Brick(Brick::BrickType type, int x, int y) {
    ImageManager* im = ImageManager::instance();

    m_brick.type = type;
    setPosition(Set, x, y);
    setSize(Set, 64, 32);

    std::string texture;
    switch(type) {
        case Hard:
            texture = "brick_hard";
            m_brick.strong = true;
            break;
        case Obstacle:
            texture = "brick_obs";
            break;
        default:
            texture = "brick";
            break;
    }

    m_brick.image = im->Clone(texture, x, y, getSize().x, getSize().y);
}

Brick::~Brick() {
    ImageManager::instance()->Remove(m_brick.image);
}

bool Brick::IsHit() {
    return isHit;
}

Brick::BrickType Brick::GetType() {
    return m_brick.type;
}

void Brick::Hit() {
    if (!m_brick.image->isViewable())
        return;

    switch(m_brick.type) {
        case Hard:
            //m_brick.image->ChangeImage("brick");
            //m_brick.image->setViewable(false);
            m_brick.image->setColor(255, 0, 0, 255);
            m_brick.type = Normal;
            break;
        default:
            m_brick.image->setViewable(false);
            isHit = true;
            break;
    }
}

void Brick::SetColor(int r, int g, int b) {
    m_brick.image->setColor(r, g, b, 255);
}