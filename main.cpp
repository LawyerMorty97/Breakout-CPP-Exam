#include <iostream>

#include "src/Core.h"

Core* core;

int main() {
    core = Core::instance();
    core->Setup("Breakout Exam", 1280, 720);

    delete core;

    return 0;
}