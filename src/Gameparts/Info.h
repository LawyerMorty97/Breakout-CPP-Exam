//
// Created by Mathias Berntsen on 23/04/2019.
//

#ifndef C_EXAM_INFO_H
#define C_EXAM_INFO_H

#include <tuple>
#include "../Components/Image.h"
#include "../Managers/ImageManager.h"
#include "../Components/Screen.h"
#include "../Components/Font.h"
#include "../Components/Text.h"

#include "../Components/IComponent.h"
#include "../Components/IGame.h"

class Info : public IComponent, IGame {
public:
    Info(const char* name);
    ~Info();

    void Draw();
private:
    ImageManager* _imgManager;
    Screen* _screen;

    Image* background_header, *background_body;

    // Fonts
    Font* chaletBig, *chaletSmall;
    Text* title, *subtitle;

    Text* scoreText, *livesText;
    Text* gameoverText, *pauseText, *winText;

};


#endif //C_EXAM_INFO_H
