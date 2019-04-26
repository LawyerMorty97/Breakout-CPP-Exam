//
// Created by Mathias Berntsen on 23/04/2019.
//

#include "Screen.h"

Screen* Screen::inst_ = NULL;

Screen* Screen::instance() {
    if (inst_ == NULL)
        inst_ = new Screen();

    return inst_;
}

IPosition::vec2 Screen::center() {
    int centerX = m_screenW / 2;
    int centerY = m_screenH / 2;

    return IPosition::vec2(centerX, centerY);
}

IPosition::vec2 Screen::center(int x, int y) {
    IPosition::vec2 c = center() - (IPosition::vec2(x, y) / 2);

    return c;
}

IPosition::vec2 Screen::corner(ScreenCorners corner) {
    IPosition::vec2 v_corner;

    switch(corner) {
        case TopLeft:
            v_corner.x = 0;
            v_corner.y = 0;
            break;
        case TopRight:
            v_corner.x = m_screenW;
            v_corner.y = 0;
            break;
        case BottomLeft:
            v_corner.x = 0;
            v_corner.y = m_screenH;
            break;
        case BottonRight:
            v_corner.x = m_screenW;
            v_corner.y = m_screenH;
            break;
    }

    return v_corner;
}

IPosition::vec2 Screen::corner(int x, int y, Screen::ScreenCorners corner) {
    IPosition::vec2 v_corner;

    switch(corner) {
        case TopLeft:
            v_corner.x = 0;
            v_corner.y = 0;
            break;
        case TopRight:
            v_corner.x = m_screenW - x;
            v_corner.y = 0;
            break;
        case BottomLeft:
            v_corner.x = 0;
            v_corner.y = m_screenH - y;
            break;
        case BottonRight:
            v_corner.x = m_screenW - x;
            v_corner.y = m_screenH - y;
            break;
    }

    return v_corner;
}

void Screen::set(int w, int h) {
    if (m_set)
        return;

    m_screenW = w;
    m_screenH = h;

    m_set = true;
}