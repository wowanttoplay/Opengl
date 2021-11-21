
#include <glew.h>
#include <glfw3.h>
#include "window/Window.h"
#include "Scene.h"
#include "glog/logging.h"


using namespace std;
bool InitGlew() {
    // init glew
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        LOG_AT_LEVEL(google::ERROR) << "Failed to initialize GLEW" << endl;
        return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);
    google::SetStderrLogging(google::ERROR);
    FLAGS_colorlogtostderr = true;

    GLFWwindow *window = Window::InitGLFWWindow();
    if (window == nullptr) {
        return -1;
    }
    if (!InitGlew()) {
        return -1;
    }
    auto[width, height] = Window::GetWindowSize(const_cast<GLFWwindow*>(window));
    glViewport(0, 0, width, height);

    Scene scene(width, height);
    scene.Init();

    function<void(int,int)>func = [&scene](int key, int action)->void{
        scene.process_key(key, action);
    };
    Window::func = &func;
    glEnable(GL_DEPTH_TEST);

    // render
    while (!glfwWindowShouldClose(const_cast<GLFWwindow*>(window))) {
        glClearColor(0.2, 0.2 ,0.2 ,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene.Update((float)glfwGetTime());
        scene.Draw();

        glfwSwapBuffers(const_cast<GLFWwindow*>(window));
        glfwPollEvents();
    }
    //exist
    glfwTerminate();
    return 0;
}






