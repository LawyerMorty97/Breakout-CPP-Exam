//
// Created by Mathias Berntsen on 23/04/2019.
//

#include "../Components/IComponent.h"
#include "Info.h"

Info::Info(const char* name) {
    _imgManager = GetImageManager();
    _screen = GetScreen();

    // Fonts
    chaletBig = new Font("content/fonts/chalet.ttf", 40);
    chaletSmall = new Font("content/fonts/chalet.ttf", 20);

    // Title
    title = new Text(chaletBig, name);
    IPosition::vec2 ttSize = title->getSize();
    title->setPosition(Text::Set, _screen->corner(ttSize.x, ttSize.y, Screen::TopRight));

    // Subtitle
    subtitle = new Text(chaletSmall, "By Mathias Berntsen");
    IPosition::vec2 sbSize = subtitle->getSize();
    subtitle->setPosition(Text::Set, _screen->corner(sbSize.x, sbSize.y, Screen::TopRight));

    const int width = 300;
    const int header_height = 128;
    // Header
    background_header = _imgManager->Add("header_bg", "interaction_bgd.png", 0, 0, width, header_height);
    background_header->setPosition(Image::Set, _screen->corner(width, header_height, Screen::TopRight));
    // Body
    int h = Screen::instance()->ScreenHeight - header_height;
    background_body = _imgManager->Add("gradient_bg", "gradient_bgd.png", 0, 0, width, h);
    background_body->setPosition(Image::Set, _screen->corner(width, h, Screen::TopRight));
    background_body->setPosition(Image::Modify, 0, header_height);

    // Header Text
    int headerX = (-width / 2) + (ttSize.x / 2);
    int headerY = (header_height / 2) - (ttSize.y / 2);
    title->setPosition(Text::Modify, headerX, headerY);

    int subX = (-width / 2) + (sbSize.x / 2);
    int subY = (header_height / 2) + (ttSize.y / 2) + (sbSize.y / 2);
    subtitle->setPosition(Text::Modify, subX, subY);

    scoreText = new Text(chaletSmall, "Score: 0");
    livesText = new Text(chaletSmall, "Lives: 0");

    gameoverText = new Text(chaletBig, "Game Over");
    pauseText = new Text(chaletBig, "Paused");
    winText = new Text(chaletBig, "Congratulations");


    scoreText->setPosition(Text::Set, background_body->getPosition());
    scoreText->setPosition(Text::Modify, 150 - (scoreText->getSize().x / 2), 24);

    livesText->setPosition(Text::Set, background_body->getPosition());
    livesText->setPosition(Text::Modify, 150 - (livesText->getSize().x / 2), 48);

    gameoverText->setPosition(Text::Set, background_body->getPosition());
    gameoverText->setPosition(Text::Modify, 150 - (gameoverText->getSize().x / 2), background_body->getSize().y - gameoverText->getSize().y - 128);

    pauseText->setPosition(Text::Set, background_body->getPosition());
    pauseText->setPosition(Text::Modify, 150 - (pauseText->getSize().x / 2), background_body->getSize().y - pauseText->getSize().y - 128);

    winText->setPosition(Text::Set, background_body->getPosition());
    winText->setPosition(Text::Modify, 150 - (winText->getSize().x / 2), background_body->getSize().y - winText->getSize().y - 128);
}

Info::~Info() {
    delete title, subtitle, scoreText, livesText;
    delete chaletBig, chaletSmall;

    delete gameoverText, pauseText;
}

void Info::Draw() {
    background_header->Draw();
    background_body->Draw();

    std::string score = "Score: " + Utils::intToString(GetGame()->GetScore());
    std::string lives = "Lives: " + Utils::intToString(GetGame()->GetLives());
    scoreText->setText(score.c_str());
    livesText->setText(lives.c_str());

    title->Draw();
    subtitle->Draw();
    scoreText->Draw();
    livesText->Draw();

    if (GetGame()->IsGamePaused())
        pauseText->Draw();
    else if (GetGame()->IsGameOver())
        if (GetGame()->DidPlayerWin())
            winText->Draw();
        else
            gameoverText->Draw();
}