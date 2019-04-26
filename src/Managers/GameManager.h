//
// Created by Mathias Berntsen on 25/04/2019.
//

#ifndef BREAKOUT_EXAM_GAMEMANAGER_H
#define BREAKOUT_EXAM_GAMEMANAGER_H

#define SCORE_PER_HIT 150
#define LIVES 5

#include <iostream>
#include <vector>
#include <stdlib.h>

#include "../Components/Screen.h"
#include "../Managers/ImageManager.h"
#include "../Managers/InputManager.h"
#include "../Managers/GameManager.h"

class GameManager {
public:
    static GameManager* instance();

    int GetScore();
    int UpdateScore();

    int GetLives();
    int UpdateLives();

    void Pause();

    void GameOver(bool endState = false);
    void Reset();

    bool DidPlayerWin();
    bool IsGameOver();
    bool IsGamePaused();
protected:
    bool paused;
    bool game_over;
    bool won;

    int m_score;
    int m_lives;
private:
    static GameManager* inst_;

    InputManager* inputManager;
    ImageManager* imageManager;

    GameManager();
};


#endif //BREAKOUT_EXAM_GAMEMANAGER_H
