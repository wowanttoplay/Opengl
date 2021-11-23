//
// Created by virgil on 2021/6/10.
//

#include "Scene.h"
#include "ResourceManager.h"
#include "RenderObject/Box.h"
#include "RenderObject/Sphere.h"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glog/logging.h"

using namespace std;
using namespace google;


Scene::~Scene() {
    LOG_AT_LEVEL(ERROR) << "~Scene(), ptr : " << this;
}

void Scene::Draw() {
    for (auto object : objects_) {
        object->Draw();
    }
}

void Scene::Update(float dt) {

}

Scene::Scene(uint32_t width, uint32_t height, const string& resource_dir) : width_(width), height_(height) {
    LOG_AT_LEVEL(ERROR) << "Scene()" << ", ptr : " << this;
    camera_ = make_shared<Camera>(glm::vec3(0.0, 0.0, 3.0f));
    resource_manager_ = make_shared<ResourceManager>(resource_dir);
    CHECK(camera_ != nullptr);
    CHECK(resource_manager_ != nullptr);
}

void Scene::ProcessKey(int key, int action) {
    const float kDeltatime = 0.2f;
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        camera_->ProcessKeyboard(Camera_Movement::FORWARD, kDeltatime);
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        camera_->ProcessKeyboard(Camera_Movement::BACKWARD, kDeltatime);
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        camera_->ProcessKeyboard(Camera_Movement::LEFT, kDeltatime);
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        camera_->ProcessKeyboard(Camera_Movement::RIGHT, kDeltatime);
}

void Scene::MouseCallBack(double x, double y) {
    // 为了避免剧烈抖动，需要在鼠标第一次返回位置时，确立鼠标的初始位置，不做移动
    static bool first = true;
    static double x_pos_last = 0.0, y_pos_last = 0.0;

    if (first) {
        x_pos_last = x;
        y_pos_last = y;
        first = false;
    }
    double x_offset = x - x_pos_last;
    double y_offset = y - y_pos_last;
    x_pos_last = x;
    y_pos_last = y;
    camera_->ProcessMouseMovement(x_offset, y_offset);
}

void Scene::MouseScrollCallBack(double x_offset, double y_offset) {
    camera_->ProcessMouseScroll(y_offset);
}

std::shared_ptr<Camera> Scene::GetCamera() {
    return camera_;
}

std::shared_ptr<ResourceManager> Scene::GetResourceManager() {
    return resource_manager_;
}

void Scene::PushObject(std::shared_ptr<BaseObject> object) {
    if (!object) {
        LOG(ERROR) << "Push object is nullptr";
        return;
    }

    LOG(WARNING) << "push object in scene, object : " << object;
    objects_.push_back(object);
    LOG(WARNING) << "current objects size : " << objects_.size();
}
