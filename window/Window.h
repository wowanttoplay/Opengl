//
// Created by virgil on 2021/5/25.
//
#pragma once

#include <glew.h>
#include <glfw3.h>

#include <iostream>
#include <string>
#include <tuple>


class Window {
public:
    static GLFWwindow *InitGLFWWindow();

    static std::tuple<int, int> GetWindowSize(GLFWwindow *window);

private:
    static void Key_CallBack(GLFWwindow *window, int key, int scancode, int action, int mode);
};




