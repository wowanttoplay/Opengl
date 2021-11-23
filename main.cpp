
#include <glew.h>
#include <glfw3.h>
#include "window/Window.h"
#include "Scene.h"
#include "glog/logging.h"
#include "ResourceManager.h"
#include "RenderObject/BaseObject.h"
#include "RenderObject/Plane.h"


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

void AddObjectToScene(const std::shared_ptr<Scene>& scene);

int main(int argc, char* argv[]) {
    // 初始化glog
    google::InitGoogleLogging(argv[0]);
    google::SetStderrLogging(google::WARNING);
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

    // 初始化资源目录
    std::string resource_dir = getcwd(nullptr, 0);
    resource_dir = resource_dir.substr(0, resource_dir.rfind('/'));
    auto scene = make_shared<Scene>(width, height, resource_dir + "/Data/");

    function<void(int,int)>key_func = [&scene](int key, int action)->void{
        scene->ProcessKey(key, action);
    };
    function<void(double, double)> mouse_func = [&scene](double x, double y)->void{
        scene->MouseCallBack(x, y);
    };
    function<void(double, double)> mouse_scroll_func = [&scene](double x, double y)->void{
        scene->MouseScrollCallBack(x, y);
    };

    AddObjectToScene(scene);

    Window::window_key_func = &key_func;
    Window::window_mouse_func = &mouse_func;
    Window::window_mouse_scroll_func = &mouse_scroll_func;

    glEnable(GL_DEPTH_TEST);
    // render
    while (!glfwWindowShouldClose(const_cast<GLFWwindow*>(window))) {
        glClearColor(0.2, 0.2 ,0.2 ,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene->Update((float)glfwGetTime());
        scene->Draw();
        glfwSwapBuffers(const_cast<GLFWwindow*>(window));
        glfwPollEvents();
    }
    //exist
    glfwTerminate();
    return 0;
}

void AddObjectToScene(const std::shared_ptr<Scene>& scene) {
    shared_ptr<Plane> ground = std::make_shared<Plane>(scene, glm::vec3(3.0f, 1.0f, 3.0f), glm::vec3(0.0f, -0.1f, 0.0f));
    scene->PushObject(ground);
}





