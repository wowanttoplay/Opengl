//
// Created by virgil on 2021/5/25.
//

#include "Window.h"

using namespace std;

const GLuint window_width = 800;
const GLuint window_height = 600;
const std::string window_title = "LearnOpenGL";

GLFWwindow *Window::InitGLFWWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow *window = glfwCreateWindow(window_width, window_height, window_title.c_str(), nullptr, nullptr);

    if (window == nullptr) {
        cout << "Faild to create GLFW window" << endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, Key_CallBack);
    return window;
}

void Window::Key_CallBack(GLFWwindow *window, int key, int scancode, int action, int mode) {
    cout << " key call back, key = " << key << endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

std::tuple<int, int> Window::GetWindowSize(GLFWwindow *window) {
    int width = 0, height = 0;
    glfwGetFramebufferSize(window, &width, &height);
    return make_tuple(width, height);
}
