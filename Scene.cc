//
// Created by virgil on 2021/6/10.
//

#include "Scene.h"
#include "ResourceManager.h"
#include "RenderObject/Plane.h"
#include "RenderObject/Box.h"
#include "RenderObject/Sphere.h"
#include "RenderPass/ShadowProcess.h"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glog/logging.h"

using namespace std;
using namespace google;


Scene::~Scene() {
    ResourceManager::Clear();
}


void Scene::Init() {
    camera_position = glm::vec3(2.0f, 5.0f, 5.0f);
    looked_direction = glm::vec3(0, -5, -3);
    looked_position = camera_position + looked_direction;
}

void Scene::Render() {

}


void Scene::Update(float dt) {

}

void Scene::process_key(int key, int action) {

}
