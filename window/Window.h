//
// Created by virgil on 2021/5/25.
//
#pragma once

#include <glew.h>
#include <glfw3.h>

#include <iostream>
#include <string>
#include <tuple>
#include <functional>


class Window {
public:
    static GLFWwindow *InitGLFWWindow();

    static std::tuple<int, int> GetWindowSize(GLFWwindow *window);

    /**
     * 按键触发回调
     */
    static std::function<void(int, int)>* window_key_func;

    /**
     * 鼠标位置回调
     */
    static std::function<void(double, double)>* window_mouse_func;

    /**
     * 鼠标滚轮回调
     */
    static std::function<void(double, double)>* window_mouse_scroll_func;

private:
    static void Key_CallBack(GLFWwindow *window, int key, int scancode, int action, int mode);

    static void Mouse_CallBack(GLFWwindow *window, double x, double y);

    static void Mouse_ScrollCallBack(GLFWwindow *window, double x, double y);
};




