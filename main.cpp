
#include <glew.h>
#include <glfw3.h>
#include <cmath>
#include "window/Window.h"
#include "Thread/ThreadPool.h"
#include "Thread/Task.h"
#include "Tool/PrintTool.h"
#include "Log/LogUtil.h"
#include "Scene.h"

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
    log_level = LogLevel::LogLevel_Error;
    GLFWwindow *window = Window::InitGLFWWindow();
    if (window == nullptr) {
        return -1;
    }
    if (!InitGlew()) {
        return -1;
    }
    auto[width, height] = Window::GetWindowSize(const_cast<GLFWwindow*>(window));
    glViewport(0, 0, width, height);

    Scene scene;
    scene.Init();
    scene.SetView(width, height);
    function<void(int,int)>func = [&scene](int key, int action)->void{
        scene.process_key(key, action);
    };
    Window::func = &func;
//    std::bind(Window::func, &Scene::process_key, scene);

    // render
    while (!glfwWindowShouldClose(const_cast<GLFWwindow*>(window))) {

        glClearColor(0.2, 0.2 ,0.2 ,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene.Update((float)glfwGetTime());
        scene.Render();

        glfwSwapBuffers(const_cast<GLFWwindow*>(window));
        glfwPollEvents();
    }
    //exist
    glfwTerminate();
    return 0;
}






