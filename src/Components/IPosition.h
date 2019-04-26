//
// Created by Mathias Berntsen on 24/04/2019.
//

#ifndef C_EXAM_IPOSITION_H
#define C_EXAM_IPOSITION_H

#include <math.h>
#include <SDL.h>
#include <iostream>

class IPosition {
public:
    enum Direction {
        Up,
        Down,
        Left,
        Right
    };

    struct vec2 {
        float x;
        float y;

        vec2(float x = 0, float y = 0) {
            this->x = x;
            this->y = y;
        }

        vec2 clamp(float min, float max) {
            return vec2(std::max(min, std::min(max, x)), std::max(min, std::min(max, y)));
        }

        vec2 clamp(vec2 min, vec2 max) {
            float x = std::max(min.x, std::min(max.x, x));
            float y = std::max(min.y, std::min(max.y, y));

            return vec2(x, y);
        }

        vec2 divide(float n) {
            return vec2(x / n, y / n);
        }

        float magnitude() {
            float powX = x * x;
            float powY = y * y;
            return sqrt(powX + powY);
        }

        float dot(vec2 a, vec2 b) {
            float _x = a.x * b.x;
            float _y = a.y * b.y;

            return (_x + y);
        }

        vec2 normalize() {
            float mag = magnitude();
            vec2 div(1, 1);
            if (mag > 0)
                div = divide(mag);

            return div;
        }

        vec2 operator+(float a) {
            return vec2(x + a, y + a);
        }

        vec2 operator/(float a) {
            return vec2(x / a, y / a);
        }

        vec2 operator-(float a) {
            return vec2(x - a, y - a);
        }

        vec2 operator*(float a) {
            return vec2(x * a, y * a);
        }

        vec2 operator+(vec2 a) {
            return vec2(a.x + x, a.y + y);
        }

        vec2 operator/(vec2 a) {
            return vec2(a.x / x, a.y / y);
        }

        vec2 operator-(vec2 a) {
            return vec2(a.x - x, a.y - y);
        }

        vec2 operator*(vec2 a) {
            return vec2(a.x * x, a.y * y);
        }

        vec2 operator-() {
            return vec2(-x, -y);
        }
    };

    typedef std::tuple<bool, Direction, vec2> Collision;

    struct rect_t {
        float x;
        float y;
        float w;
        float h;

        SDL_Rect sdl_rect() {
            return {(int)x, (int)y, (int)w, (int)h};
        }
    };

    enum SetType {
        Set,
        Modify,
    };

    vec2 setPosition(SetType type, float x, float y) {
        switch(type) {
            case Modify:
                _x += x;
                _y += y;
                break;
            default:
                _x = x;
                _y = y;
                break;
        }

        rect.x = _x;
        rect.y = _y;

        return vec2(_x, _y);
    }

    vec2 setPosition(SetType type, vec2 position) {
        vec2 new_pos = setPosition(type, position.x, position.y);

        return new_pos;
    }

    vec2 setSize(SetType type, float w, float h) {
        switch(type) {
            case Modify:
                _w += w;
                _h += h;
                break;
            default:
                _w = w;
                _h = h;
                break;
        }

        rect.w = _w;
        rect.h = _h;

        return vec2(_w, _h);
    }

    vec2 setSize(SetType type, vec2 size) {
        vec2 new_size = setSize(type, size.x, size.y);

        return new_size;
    }

    vec2 getPosition() {
        return vec2(rect.x, rect.y);
    }

    vec2 getSize() {
        return vec2(rect.w, rect.h);
    }

    Direction getDirection(vec2 target) {
        vec2 directions[] = {
                vec2(0.f, 1.f),
                vec2(0.f, -1.f),
                vec2(1.f, 0.f),
                vec2(-1.f, 0.f)
        };

        float max = 0.f;
        int best_match = -1;

        for (int i = 0; i < 4; i++) {
            float dotp = target.dot(target.normalize(), directions[i]);
            if (dotp > max) {
                max = dotp;
                best_match = i;
            }
        }

        return (Direction)best_match;
    }

protected:
    SDL_Rect rect;
private:
    float _x, _y;
    float _w, _h;
};

#endif //C_EXAM_IPOSITION_H
