//
// Created by Mathias Berntsen on 25/04/2019.
//

#include "Board.h"

Board::Board() {
    game = GetGame();
    input = GetInputManager();
    imageManager = GetImageManager();
    screen = GetScreen();

    int borderPos = 10;
    int borderSize = 20;
    IPosition::vec2 size = screen->corner(Screen::BottonRight);

    size.x -= 300;

    setPosition(Set, borderPos, borderPos);
    setSize(Set, size.x - borderPos, size.y - borderPos);

    font = new Font("content/fonts/chalet.ttf", 40);

    board = imageManager->Add("board", "board.png", 0, 0, 128, 23);
    board->setPosition(Set, (rect.w / 2) - (board->getSize().x / 2), screen->ScreenHeight - 100);

    float ballX = (rect.w / 2) - 32;
    ball = new Ball(vec2(ballX, screen->ScreenHeight - 148), 12.5f, vec2(0.1f, -0.1f));

    imageManager->Add("brick", "brick.png", 0, 0, 64, 32)->setViewable(false);
    imageManager->Add("brick_hard", "brick_hard.png", 0, 128, 64, 32)->setViewable(false);
    imageManager->Add("brick_obs", "brick_locked.png", 0, 256, 64, 32)->setViewable(false);

    //imageManager = GetImageManager();
    int cols = 12;
    int rows = 10;
    int startX = 65;
    //int startX = 100;
    int startY = 65;
    for (int i = 0; i < 10; i++) {
        int r, g, b;
        r = rand() % 255;
        g = rand() % 255;
        b = rand() % 255;
        for (int j = 0; j < 8; j++) {
            Brick::BrickType tp = i % 2 == 0 ? Brick::Normal : Brick::Hard;

            int bX = startX + (72 * i);
            int bY = startY + (j * 40);

            Brick* br = new Brick(tp, bX, bY);
            br->SetColor(r, g, b);
            bricks.push_back(br);
        }
    }
}

Board::~Board() {
    delete font;
    delete ball;
}

bool Board::CheckCollisions(IPosition object) {
    bool cX = object.getPosition().x + object.getSize().x >= ball->getPosition().x &&
              ball->getPosition().x + ball->getSize().x >= object.getPosition().x;

    if (cX)
        ball->vel.x = -ball->vel.x;

    // (Brick.y + Brick.h) >= Ball.y && (Ball.y + Ball.h) >= Brick.y
    bool cY = object.getPosition().y + object.getSize().y >= ball->getPosition().y &&
              ball->getPosition().y + ball->getSize().y >= object.getPosition().y;

    if (cY)
        ball->vel.y = -ball->vel.y;

    return cX && cY;
}

void Board::Update(float deltaTime) {
    if (input->KeyDown(SDL_SCANCODE_SPACE) && !game->IsGameOver() && !ball->stuck)
        game->Pause();

    if (game->IsGamePaused() || game->IsGameOver()) {
        return;
    }

    ball->Move(deltaTime);

    float moveX = 0.2f;
    if (input->KeyStillDown(SDL_SCANCODE_A)) {
        if (board->getPosition().x > rect.x) {
            board->setPosition(Modify, -moveX, 0);

            if (ball->stuck) {
                ball->setPosition(Modify, -moveX, 0);
            }
        }
    }

    if (input->KeyStillDown(SDL_SCANCODE_D)) {
        if ((board->getPosition().x + board->getSize().x) <= rect.w) {
            board->setPosition(Modify, moveX, 0);

            if (ball->stuck) {
                ball->setPosition(Modify, moveX, 0);
            }
        }
    }

    if (ball->stuck && input->KeyDown(SDL_SCANCODE_SPACE))
        ball->stuck = false;

    for(std::vector<Brick*>::iterator it = bricks.begin(); it != bricks.end(); ++it) {
        Brick* brick = *it;

        if (CheckCollisions(*brick) && !brick->IsHit()) {
            if (brick->GetType() != Brick::BrickType::Obstacle) {
                brick->Hit();
                GetGame()->UpdateScore();

                bricks.erase(it);
                delete brick;
                break;
            }

            printf("Bricks left: %d", bricks.size());
            if (bricks.size() == 0)
                GetGame()->GameOver(true);
        }
    }

    /*
    for (Brick* brick : bricks) {
        if (CheckCollisions(*brick) && !brick->IsHit()) {
            if (brick->GetType() != Brick::BrickType::Obstacle) {
                brick->Hit();
                GetGame()->UpdateScore();
            }

            if (brick->GetType() == Brick::Hard) {
                auto b = new Brick(Brick::Normal, brick->getPosition().x, brick->getPosition().y);
            }
            bricks.pop_back();
            delete brick;

            printf("Bricks left: %d", bricks.size());
            if (bricks.size() == 0)
                GetGame()->GameOver(true);

            break;
        }
    }*/

    //bool board_col = CheckCollisions(*board);
    if (!ball->stuck) {
        if (ball->getPosition().y > (board->getPosition().y + board->getSize().y))
            return;

        if (ball->getPosition().x >= board->getPosition().x && ball->getPosition().x <= (board->getPosition().x + board->getSize().x)) {
            if ((ball->getPosition().y + ball->getSize().y) >= board->getPosition().y) {
                float center = board->getPosition().x + board->getSize().x / 2;
                float dist = (ball->getPosition().x + ball->radius) - center;
                float percentage = dist / (board->getSize().x / 2.f);

                float strength = 2.0f;
                vec2 old_vel = ball->vel;
                ball->vel.x = 0.1f * percentage * strength;
                //ball->vel.y = -ball->vel.y;
                ball->vel.y = -1 * abs(ball->vel.y);
                ball->vel = ball->vel.normalize() * old_vel.magnitude();
            }
        }
    }
}

void Board::Draw(float deltaTime) {
    SDL_SetRenderDrawColor(GetRenderer(), 255, 255, 255, 255);
    SDL_RenderDrawLine(GetRenderer(), board->getPosition().x, board->getPosition().y, ball->getPosition().x, ball->getPosition().y);
    SDL_RenderPresent(GetRenderer());
}