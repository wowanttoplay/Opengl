//
// Created by virgil on 2021/6/10.
//

#include "Scene.h"
#include "ResourceManager.h"
#include "RenderObject/Box.h"
#include "glm/gtx/string_cast.hpp"
#include "glog/logging.h"

using namespace std;
using namespace google;


Scene::~Scene() {
    LOG_AT_LEVEL(ERROR) << "~Scene(), ptr : " << this;
}

void Scene::draw() {
    // 检测是否绘制阴影
    if (open_shadow_) drawShaow();
    normalDraw();
}

void Scene::normalDraw() {
    glViewport(0, 0, width_, height_);
    glClearColor(0.2, 0.2 , 0.2 , 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (const auto &object: objects_) {
        object->draw();
    }
    light_->draw();
}

void Scene::drawShaow() {
    const uint32_t kShadowWidth = 1024;
    glViewport(0, 0, kShadowWidth, kShadowWidth);
    if (!glIsFramebuffer(FBO_)) {
        glGenFramebuffers(1, &FBO_);
    }
    if (!shadow_map_) {
        shadow_map_ = make_shared<Texture2D>(GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT, GL_FLOAT);
        shadow_map_->generate(kShadowWidth, kShadowWidth, nullptr);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, FBO_);
    shadow_map_->bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadow_map_->getId(), 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glClear(GL_DEPTH_BUFFER_BIT);
    for (const auto &object: objects_) {
        object->drawShadow();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Scene::Update() {

}

Scene::Scene(uint32_t width, uint32_t height, const string &resource_dir) : width_(width), height_(height) {
    LOG_AT_LEVEL(ERROR) << "Scene()" << ", ptr : " << this;
    resource_manager_ = make_shared<ResourceManager>(resource_dir);
    CHECK(resource_manager_ != nullptr);
}

void Scene::processKey(int key, int action) {
    const float kDeltatime = 0.1f;
    if (key == GLFW_KEY_W)
        camera_->ProcessKeyboard(Camera_Movement::FORWARD, kDeltatime);
    if (key == GLFW_KEY_S)
        camera_->ProcessKeyboard(Camera_Movement::BACKWARD, kDeltatime);
    if (key == GLFW_KEY_A)
        camera_->ProcessKeyboard(Camera_Movement::LEFT, kDeltatime);
    if (key == GLFW_KEY_D)
        camera_->ProcessKeyboard(Camera_Movement::RIGHT, kDeltatime);
}

void Scene::mouseCallBack(double x, double y) {
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

void Scene::mouseScrollCallBack(double x_offset, double y_offset) {
    camera_->ProcessMouseScroll(y_offset);
}

std::shared_ptr<Camera> Scene::getCamera() {
    return camera_;
}

std::shared_ptr<ResourceManager> Scene::getResourceManager() {
    return resource_manager_;
}

void Scene::pushObject(std::shared_ptr<BaseObject> object) {
    if (!object) {
        LOG(ERROR) << "Push object is nullptr";
        return;
    }

    LOG(WARNING) << "push object in scene, object : " << object;
    objects_.push_back(object);
    LOG(WARNING) << "current objects size : " << objects_.size();
}

void Scene::setLight(const shared_ptr<BaseLight> &light) {
    light_ = light;
}

const shared_ptr<BaseLight> &Scene::getLight() const {
    return light_;
}

void Scene::setCamera(const shared_ptr<Camera> &camera) {
    camera_ = camera;
}

void Scene::setOpenShadow(bool openShadow) {
    open_shadow_ = openShadow;
}

const shared_ptr<Texture2D> &Scene::getShadowMap() const {
    return shadow_map_;
}

