//
// Created by mmfij on 2/20/2019.
//

#ifndef C_ARBEIDSKRAV_IMAGEMANAGER_H
#define C_ARBEIDSKRAV_IMAGEMANAGER_H

#include <iostream>
#include <map>
#include <SDL.h>
#include <SDL_image.h>

#include "../Components/Image.h"

class ImageManager {
public:
    static ImageManager* instance();
    ~ImageManager();

    Image* Add(std::string name, std::string file, int x, int y, int w, int h);
    Image* Get(std::string name);
    void Draw();
protected:
    std::map<std::string, Image*> images;
private:
    static ImageManager *inst_;

    ImageManager() {
    }
};


#endif //C_ARBEIDSKRAV_IMAGEMANAGER_H
