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

class Info : public IComponent {
public:
    Info();
    ~Info();

    void Draw();
private:
    Image* background_header, *background_body;
    Image* star_a, *star_b;

    // Fonts
    Font* chaletBig, *chaletSmall;
    Text* title, *subtitle;
};


#endif //C_EXAM_INFO_H
