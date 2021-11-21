//
// Created by virgil on 2021/5/25.
//

#include "Window.h"
#include "glog/logging.h"

using namespace std;
using namespace google;

const GLuint window_width = 800;
const GLuint window_height = 600;
const std::string window_title = "LearnOpenGL";
function<void(int, int)>* Window::func = nullptr;

GLFWwindow *Window::InitGLFWWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow *window = glfwCreateWindow(window_width, window_height, window_title.c_str(), nullptr, nullptr);

    if (window == nullptr) {
        LOG_AT_LEVEL(ERROR) << "Faild to create GLFW window";
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, Key_CallBack);
    return window;
}

void Window::Key_CallBack(GLFWwindow *window, int key, int scancode, int action, int mode) {
    LOG_AT_LEVEL(INFO) << " key call back, key = " << key;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (func != nullptr) {
        (*func)(key, action);
    }
}

std::tuple<int, int> Window::GetWindowSize(GLFWwindow *window) {
    int width = 0, height = 0;
    glfwGetFramebufferSize(window, &width, &height);
    return make_tuple(width, height);
}
