//
// Created by mmfij on 2/20/2019.
//

#include "ImageManager.h"

ImageManager* ImageManager::inst_ = NULL;

ImageManager* ImageManager::instance() {
    if (inst_ == NULL) {
        inst_ = new ImageManager();
    }

    return inst_;
}

ImageManager::~ImageManager() {
    for (std::map<std::string, Image*>::iterator it = images.begin(); it != images.end(); it++) {
        Image* image = it->second;
        delete image;
    }

    images.clear();
}

Image* ImageManager::Add(std::string name, std::string image, int x, int y, int w, int h) {
    Image* new_image = new Image(image, x, y, w, h);

    images[name] = new_image;

    return new_image;
}

Image* ImageManager::Clone(std::string name) {
    Image* image = nullptr;

    if (images[name] != nullptr) {
        Image* parent = images[name];
        std::pair pos = parent->getPosition();
        std::pair size = parent->getSize();

        //image = new Image(images[name]->filename, pos.first, pos.second, size.first, size.second);
        std::string clone_id = name + "_clone_" + Utils::randomString(10);

        image = Add(clone_id, parent->filename, pos.first, pos.second, size.first, size.second);
        //image = parent;
    }

    return image;
}

Image* ImageManager::Get(std::string name) {
    Image* image = nullptr;

    if (images[name] != nullptr)
        image = images[name];
    /*if (buffer[index] != nullptr)
        image = buffer[index];*/

    return image;
}

void ImageManager::Draw() {
    for (std::map<std::string, Image*>::iterator it = images.begin(); it != images.end(); it++) {
        if (it->second->isViewable())
            it->second->Draw();
    }
}