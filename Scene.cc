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
    LOG_AT_LEVEL(ERROR) << "~Scene()";
    ResourceManager::Clear();
}


void Scene::Init() {
    camera_position_ = glm::vec3(2.0f, 5.0f, 5.0f);
    looked_direction_ = glm::vec3(0, -5, -3);
    looked_position_ = camera_position_ + looked_direction_;
}

void Scene::Draw() {

}


void Scene::Update(float dt) {

}

void Scene::process_key(int key, int action) {

}

Scene::Scene(uint32_t width, uint32_t height) : width_(width), height_(height) {
    LOG_AT_LEVEL(ERROR) << "Scene()";
}
