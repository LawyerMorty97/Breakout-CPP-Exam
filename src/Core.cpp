//
// Created by Mathias Berntsen on 13/02/2019.
//

#include "Core.h"

Core* Core::inst_ = NULL;

Core* Core::instance() {
    if (inst_ == NULL) {
        inst_ = new Core;
    }

    return inst_;
}

void Core::Setup(std::string title, int w_size, int h_size) {
    this->title = title;
    w_width = w_size;
    w_height = h_size;

    SetupSDL();
    Screen::instance()->set(w_width, w_height);
    imageManager = ImageManager::instance();
    input = InputManager::instance();

    //SDL_ShowCursor(false);

    imageManager->Add("pixel", "pixel.png", 0, 0, 1, 1);
    cursor = imageManager->Add("cursor", "cursor.png", 0, 0, 32, 32);

    lineX = imageManager->Add("lineX", "pixel.png", 0, 0, w_width, 1);
    lineY = imageManager->Add("lineY", "pixel.png", 0, 0, 1, w_height);

    info = new Info(title.c_str());
    board = new Board;

    while (!quit) {
        Update();
        Draw();
    }

    Quit();
}

void Core::Quit() {
    delete input;
    delete imageManager;
    delete info, board;

    Utils::message("Destroyed SDL renderer");
    SDL_DestroyRenderer(renderer);

    Utils::message("Destroyed SDL window");
    SDL_DestroyWindow(window);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    Utils::message("Quit SDL");

    exit(EXIT_SUCCESS);
}

void Core::SetupSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        Utils::error_sdl("Unable to initalize SDL");
    else
        Utils::message("Initialized SDL");

    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    const char* c_title = Utils::stringToChar(title);

    window = SDL_CreateWindow(c_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w_width, w_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (!window)
        Utils::error_sdl("Failed to create window");
    else
        Utils::message("Created a window");

    renderer = SDL_CreateRenderer(window, 01, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        Utils::error_sdl("Failed to create renderer");
    } else {
        Utils::message("Created a SDL renderer");
    }
}

void Core::Update() {
    input->Update();
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
        }
    }
    //cursor->setPosition(Image::Set, input->MousePosition().first, input->MousePosition().second);

    dtNow = SDL_GetTicks();
    if (dtNow > dtLast) {
        deltaTime = dtNow - dtLast;
    }
    dtLast = dtNow;

    if (input->KeyUp(SDL_SCANCODE_ESCAPE))
        quit = true;

    board->Update(deltaTime);
}

void Core::Draw() {
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255); // Background Color
    SDL_RenderClear(renderer);

    imageManager->Draw();
    info->Draw();
    board->Draw(deltaTime);

    cursor->Draw();

    SDL_RenderPresent(renderer);
}

Core::~Core() {
    Quit();
}