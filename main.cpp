
#include <glew.h>
#include <glfw3.h>
#include <cmath>
#include "window/Window.h"
#include "Thread/ThreadPool.h"
#include "Thread/Task.h"
#include "shader/shader_data.h"
#include "shader/ShaderFactory.h"
#include "Data/vertex_data.h"
#include "Tool/PrintTool.h"
#include "Log/LogUtil.h"

bool InitGlew();

unsigned int createProgram();

uint32_t CreateShaderProgram(const char *vertex_shader_code, const char *fragment_shader_code);

void CreateRenderVAO(uint32_t &VBO, uint32_t &VAO, uint32_t &EBO);

using namespace std;

bool InitGlew() {
    // init glew
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "Failed to initialize GLEW" << endl;
        return false;
    }
    return true;
}

int main() {


    GLFWwindow *window = Window::InitGLFWWindow();
    if (window == nullptr) {
        return -1;
    }
    if (!InitGlew()) {
        return -1;
    }
    auto[width, height] = Window::GetWindowSize(const_cast<GLFWwindow*>(window));
    glViewport(0, 0, width, height);


    // render
    while (!glfwWindowShouldClose(const_cast<GLFWwindow*>(window))) {
        glfwPollEvents();

        glfwSwapBuffers(const_cast<GLFWwindow*>(window));
    }
    //exist
    glfwTerminate();
    return 0;
}






