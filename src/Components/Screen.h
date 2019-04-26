//
// Created by Mathias Berntsen on 23/04/2019.
//

#ifndef C_EXAM_SCREEN_H
#define C_EXAM_SCREEN_H

#include <tuple>
#include "IPosition.h"

class Screen {
public:
    enum ScreenCorners {
        TopLeft,
        TopRight,
        BottomLeft,
        BottonRight
    };

    static Screen* instance();
    ~Screen();

    const int &ScreenWidth, &ScreenHeight;

    IPosition::vec2 center();
    IPosition::vec2 center(int x, int y);

    IPosition::vec2 corner(ScreenCorners corner = TopLeft);
    IPosition::vec2 corner(int x, int y, ScreenCorners corner = TopLeft);

    void set(int w, int h);
private:
    static Screen* inst_;

    Screen() : ScreenWidth(m_screenW), ScreenHeight(m_screenH) {
    }

    int m_screenW, m_screenH = 0;
    bool m_set = false;
};


#endif //C_EXAM_SCREEN_H
