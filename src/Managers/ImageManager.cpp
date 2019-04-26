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

int ImageManager::Size() {
    return images.size();
}

Image* ImageManager::Add(std::string name, std::string image, int x, int y, int w, int h) {
    Image* new_image = new Image(image, x, y, w, h);

    images[name] = new_image;

    return new_image;
}

Image* ImageManager::Clone(std::string name, int x, int y, int w, int h) {
    Image* image = nullptr;

    if (images[name] != nullptr) {
        Image* parent = images[name];
        std::string clone_id = name + "_clone_" + Utils::randomString(10);

        image = Add(clone_id, parent->filename, x, y, w, h);
    }

    return image;
}

void ImageManager::Remove(std::string name) {
    if (images[name] != nullptr) {
        images.erase(name);
        Image* img = images[name];
        delete img;
    }
}

void ImageManager::Remove(Image *image) {
    for (std::map<std::string, Image*>::iterator it = images.begin(); it != images.end(); it++) {
        if (it->second == image) {
            images.erase(it);
            delete image;
            break;
        }
    }
}

Image* ImageManager::Clone(std::string name) {
    Image* image = nullptr;

    if (images[name] != nullptr) {
        Image* parent = images[name];
        IPosition::vec2 pos = parent->getPosition();
        IPosition::vec2 size = parent->getSize();

        image = Clone(name, pos.x, pos.y, size.x, size.y);
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