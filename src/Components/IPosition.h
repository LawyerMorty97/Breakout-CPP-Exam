//
// Created by Mathias Berntsen on 24/04/2019.
//

#ifndef C_EXAM_IPOSITION_H
#define C_EXAM_IPOSITION_H

#include <SDL.h>
#include <iostream>

class IPosition {
public:
    enum SetType {
        Set,
        Modify,
    };

    std::pair<int, int> setPosition(SetType type, int x, int y) {
        switch(type) {
            case Modify:
                this->_x += x;
                this->_y += y;
                break;
            default:
                this->_x = x;
                this->_y = y;
                break;
        }

        rect.x = _x;
        rect.y = _y;

        return {_x, _y};
    }

    std::pair<int, int> setPosition(SetType type, std::pair<int, int> position) {
        std::pair<int, int> new_pos = setPosition(type, position.first, position.second);

        return new_pos;
    }

    std::pair<int, int> setSize(SetType type, int w, int h) {
        switch(type) {
            case Modify:
                this->_w += w;
                this->_h += h;
                break;
            default:
                this->_w = w;
                this->_h = h;
                break;
        }

        rect.w = _w;
        rect.h = _h;

        return {_w, _h};
    }

    std::pair<int, int> setSize(SetType type, std::pair<int, int> size) {
        std::pair<int, int> new_size = setSize(type, size.first, size.second);

        return new_size;
    }

    std::pair<int, int> getPosition() {
        return {rect.x, rect.y};
    }

    std::pair<int, int> getSize() {
        return {rect.w, rect.h};
    }

protected:
    SDL_Rect rect;
private:
    int _x, _y;
    int _w, _h;
};

#endif //C_EXAM_IPOSITION_H
