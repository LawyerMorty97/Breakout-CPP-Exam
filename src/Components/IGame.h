//
// Created by Mathias Berntsen on 25/04/2019.
//

#ifndef BREAKOUT_EXAM_IGAME_H
#define BREAKOUT_EXAM_IGAME_H

#include "../Components/Screen.h"
#include "../Managers/ImageManager.h"
#include "../Managers/InputManager.h"
#include "../Managers/GameManager.h"

class IGame {
public:
    InputManager* GetInputManager() {
        return InputManager::instance();
    }

    ImageManager* GetImageManager() {
        return ImageManager::instance();
    }

    GameManager* GetGame() {
        return GameManager::instance();
    }

    Screen* GetScreen() {
        return Screen::instance();
    }
};

#endif //BREAKOUT_EXAM_IGAME_H
