//
// Created by Mathias Berntsen on 23/04/2019.
//

#include "../Components/IComponent.h"
#include "Info.h"

Info::Info() {
    // Fonts
    chaletBig = new Font("content/fonts/chalet.ttf", 40);
    chaletSmall = new Font("content/fonts/chalet.ttf", 20);

    // Title
    title = new Text(chaletBig, "Arkenoid");
    std::pair ttSize = title->getSize();
    title->setPosition(Text::Set, Screen::instance()->corner(ttSize.first, ttSize.second, Screen::TopRight));

    // Subtitle
    subtitle = new Text(chaletSmall, "By Mathias Berntsen");
    std::pair sbSize = subtitle->getSize();
    subtitle->setPosition(Text::Set, Screen::instance()->corner(sbSize.first, sbSize.second, Screen::TopRight));

    const int width = 300;
    const int header_height = 128;
    // Header
    background_header = new Image("interaction_bgd.png", 0, 0, width, header_height);
    background_header->setPosition(Image::Set, Screen::instance()->corner(width, header_height, Screen::TopRight));
    // Body
    int h = Screen::instance()->ScreenHeight - header_height;
    background_body = new Image("gradient_bgd.png", 0, 0, width, h);
    background_body->setPosition(Image::Set, Screen::instance()->corner(width, h, Screen::TopRight));
    background_body->setPosition(Image::Modify, 0, header_height);

    // Header Text
    int headerX = (-width / 2) + (ttSize.first / 2);
    int headerY = (header_height / 2) - (ttSize.second / 2);
    title->setPosition(Text::Modify, headerX, headerY);

    int subX = (-width / 2) + (sbSize.first / 2);
    int subY = (header_height / 2) + (ttSize.second / 2) + (sbSize.second / 2);
    subtitle->setPosition(Text::Modify, subX, subY);

    // Stars
    star_a = new Image("star.png", 0, 0, 16, 16);
    star_b = new Image("star.png", 0, 0, 16, 16);
}

Info::~Info() {
    delete title, subtitle;
    delete chaletBig, chaletSmall;
    delete background_header, background_body;
    delete star_a, star_b;
}

void Info::Draw() {
    background_header->Draw();
    background_body->Draw();
    title->Draw();
    subtitle->Draw();
}