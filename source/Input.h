//
// Created by Martin Lyrå on 2017-12-18.
//

#ifndef AMBER_SUN_INPUT_H
#define AMBER_SUN_INPUT_H

#include <GLFW/glfw3.h>

namespace Input {
    void Initialize();

    void KeyCallback(GLFWwindow* window, int key, int code, int action, int modifier);
};

#endif //AMBER_SUN_INPUT_H
