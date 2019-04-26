//
// Created by Mathias Berntsen on 25/04/2019.
//

#include "GameManager.h"

GameManager* GameManager::inst_ = NULL;

GameManager* GameManager::instance() {
    if (inst_ == NULL)
        inst_ = new GameManager;

    return inst_;
}

GameManager::GameManager() {
    imageManager = ImageManager::instance();
    inputManager = InputManager::instance();

    paused = false;
    game_over = false;
    m_score = 0;
    m_lives = LIVES;
}

void GameManager::Reset() {
    paused = false;
    game_over = false;
    m_score = 0;
    m_lives = LIVES;
}

int GameManager::GetScore() {
    return m_score;
}

int GameManager::UpdateScore() {
    m_score += SCORE_PER_HIT;

    return m_score;
}

int GameManager::GetLives() {
    return m_lives;
}

int GameManager::UpdateLives() {
    m_lives -= 1;

    if (m_lives == 0) {
        GameOver();
    }

    return m_lives;
}

void GameManager::GameOver(bool endState) {
    if (paused)
        return;

    won = endState;
    game_over = true;
}

bool GameManager::IsGameOver() {
    return game_over;
}

void GameManager::Pause() {
    paused = !paused;
}

bool GameManager::IsGamePaused() {
    return paused;
}

bool GameManager::DidPlayerWin() {
    return won;
}