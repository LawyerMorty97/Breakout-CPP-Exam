//
// Created by Mathias Berntsen on 15/02/2019.
//

#ifndef ARBEIDSKRAV_UTILS_H
#define ARBEIDSKRAV_UTILS_H

#include <iostream>
#include <algorithm>
#include <SDL.h>
#include <tuple>

class Utils {
public:
    static std::string randomString(size_t length);
    static const char* stringToChar(std::string str);
    static std::string intToString(int num);

    static SDL_Window* getWindow();
    static SDL_Renderer* getRenderer();

    static void message(std::string msg);
    static void error(std::string msg);
    static void error_sdl(std::string msg);
};


#endif //ARBEIDSKRAV_UTILS_H
