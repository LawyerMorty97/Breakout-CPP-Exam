//
// Created by Mathias Berntsen on 13/02/2019.
//

#ifndef PROJECT_CORE_H
#define PROJECT_CORE_H

#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>
#include <math.h>

#include "Utils.h"
#include "Managers/InputManager.h"
#include "Managers/ImageManager.h"

#include "Components/Screen.h"
#include "Components/Image.h"

#include "Gameparts/Info.h"
#include "Gameparts/Board.h"

class Core {
public:
    static Core* instance();

    SDL_Window* Window;
    SDL_Renderer* Renderer;

    void Setup(std::string title, int w_size, int h_size);
    ~Core();
protected:
    int w_width, w_height; // Window dimensions
    bool quit = false;

    std::string title;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    InputManager* input;
    ImageManager* imageManager;

    Image* cursor;

    Image* lineX, *lineY;
private:
    static Core* inst_;

    // Delta Time
    Uint32 dtNow, dtLast;
    float deltaTime;

    // Game Elements
    Info* info;
    Board* board;

    Core() {

    };

    void SetupSDL();
    void Quit();

    void Update();
    void Draw();
};


#endif //PROJECT_CORE_H
