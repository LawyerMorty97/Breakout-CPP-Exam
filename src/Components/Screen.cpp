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

std::pair<int, int> Screen::center() {
    int centerX = m_screenW / 2;
    int centerY = m_screenH / 2;

    return {centerX, centerY};
}

std::pair<int, int> Screen::center(int x, int y) {
    int cX = std::get<0>(center());
    int cY = std::get<1>(center());

    int centerX = cX - (x / 2);
    int centerY = cY - (y / 2);

    return {centerX, centerY};
}

std::pair<int, int> Screen::corner(ScreenCorners corner) {
    int cornerX, cornerY;

    switch(corner) {
        case TopLeft:
            cornerX = 0;
            cornerY = 0;
            break;
        case TopRight:
            cornerX = m_screenW;
            cornerY = 0;
            break;
        case BottomLeft:
            cornerX = 0;
            cornerY = m_screenH;
            break;
        case BottonRight:
            cornerX = m_screenW;
            cornerY = m_screenH;
            break;
    }

    return {cornerX, cornerY};
}

std::pair<int, int> Screen::corner(int x, int y, Screen::ScreenCorners corner) {
    int cornerX, cornerY;

    switch(corner) {
        case TopLeft:
            cornerX = 0;
            cornerY = 0;
            break;
        case TopRight:
            cornerX = m_screenW - x;
            cornerY = 0;
            break;
        case BottomLeft:
            cornerX = 0;
            cornerY = m_screenH - y;
            break;
        case BottonRight:
            cornerX = m_screenW - x;
            cornerY = m_screenH - y;
            break;
    }

    return {cornerX, cornerY};
}

void Screen::set(int w, int h) {
    if (m_set)
        return;

    m_screenW = w;
    m_screenH = h;

    m_set = true;
}