
#include <glew.h>
#include <glfw3.h>
#include "window/Window.h"
#include "Scene.h"
#include "glog/logging.h"
#include "ResourceManager.h"
#include "RenderObject/BaseObject.h"
#include "RenderObject/Plane.h"
#include "RenderObject/Box.h"
#include "RenderObject/Sphere.h"
#include "RenderObject/Light/PointLight.h"
#include "Camera.h"
#include "RenderObject/Light/BaseLight.h"

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
    auto camera = make_shared<Camera>(scene, glm::vec3(0, 6.0f, 16.0f));
    scene->setCamera(camera);
    scene->setOpenShadow(true);
    scene->setDebugShadow(true);
    scene->setOpenAo(true);
    scene->setDebugAo(true);

    function<void(int,int)>key_func = [&scene](int key, int action)->void{
        scene->processKey(key, action);
    };
    function<void(double, double)> mouse_func = [&scene](double x, double y)->void{
        scene->mouseCallBack(x, y);
    };
    function<void(double, double)> mouse_scroll_func = [&scene](double x, double y)->void{
        scene->mouseScrollCallBack(x, y);
    };

    AddObjectToScene(scene);

    Window::window_key_func = &key_func;
    Window::window_mouse_func = &mouse_func;
    Window::window_mouse_scroll_func = &mouse_scroll_func;

    glEnable(GL_DEPTH_TEST);
    // render
    glGetError();
    while (!glfwWindowShouldClose(const_cast<GLFWwindow*>(window))) {

        scene->Update();
        scene->draw();
        glfwSwapBuffers(const_cast<GLFWwindow*>(window));
        glfwPollEvents();
    }
    //exist
    glfwTerminate();
    return 0;
}

void AddObjectToScene(const std::shared_ptr<Scene>& scene) {
    shared_ptr<Plane> ground = std::make_shared<Plane>(scene, glm::vec3(40.0f), glm::vec3(0.0f, -0.002f, 0.0f));
    ground->setColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    scene->pushObject(ground);

    shared_ptr<Box> right_box = std::make_shared<Box>(scene, glm::vec3(1.0f, 2.0, 1.0), glm::vec3(2.0, 0.5f, 0.0));
    right_box->setColor(glm::vec4(0.3f, 1.0f, 0.0f, 1.0f));
    scene->pushObject(right_box);
//
    shared_ptr<Box> left_box = std::make_shared<Box>(scene, glm::vec3(1.0f, 3.0, 1.0), glm::vec3(-2.0, 0.5f, 0.0));
    left_box->setColor(glm::vec4(1.0f, 0.3f, 0.4f, 1.0f));
    scene->pushObject(left_box);

    shared_ptr<Sphere> sphere = std::make_shared<Sphere>(scene, glm::vec3(1.0f), glm::vec3(0.0f, 0.5f, 3.0f), 30, 30);
    sphere->setColor(glm::vec4(0.f, 0.f, 0.8f, 1.0f));
    scene->pushObject(sphere);

    shared_ptr<Box> right_wall = std::make_shared<Box>(scene, glm::vec3(0.1, 4.0, 5.0), glm::vec3(3.0, 2.0f, 0.0f));
    right_wall->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    scene->pushObject(right_wall);

    shared_ptr<Box> front_wall = std::make_shared<Box>(scene, glm::vec3(6.1f, 4.0f, 0.1f), glm::vec3(0.0f, 2.0f, -2.5f));
    front_wall->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    scene->pushObject(front_wall);

    shared_ptr<PointLight> light = std::make_shared<PointLight>(scene, glm::vec3(1.0f), glm::vec3(-6.0f, 9.0f,3.0f));
    light->setColor(glm::vec4(15.0f));
    light->setTarget(glm::vec3(0.0));
    light->setFarPlane(30.0f);
    light->setNearPlane(0.1f);
    scene->setLight(light);
}





