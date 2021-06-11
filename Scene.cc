//
// Created by virgil on 2021/6/10.
//

#include "Scene.h"
#include "ResourceManager.h"
#include "RenderObject/Plane.h"
#include "Log/LogUtil.h"

Plane* plane = nullptr;

const std::string kFLOOR_NAME = "floor";
void Scene::Init() {
    camera_position = glm::vec3 (0.0f, 3.0f, 10.0f);
    looked_position = camera_position + glm::vec3(0, 0 , -3);

    ResourceManager::LoadTexture("../Data/floor.jpg", kFLOOR_NAME);
    ResourceManager::LoadShader("../Data/plane.vs", "../Data/plane.fs", nullptr, kFLOOR_NAME);

    plane = new Plane();
}

void Scene::Render() {
    glm::mat4 view = glm::lookAt(camera_position, looked_position, glm::vec3(0,1,0));
    glm::mat4 projection = glm::perspective(view_angle, scene_width/scene_height, 0.1f, 100.f);
    plane->Render(ResourceManager::GetShader(kFLOOR_NAME), ResourceManager::GetTexture(kFLOOR_NAME), view, projection);
}

void Scene::SetView(float width, float height) {
    scene_width = width;
    scene_height = height;
}

void Scene::Update(float dt) {
    plane->Update(dt);
}

void Scene::process_key(int key, int action) {
    logE("scene, press key : %d", key);
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        camera_position += glm::vec3(0.0, 0.0, -1.0);
    }else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        camera_position += glm::vec3 (0.0, 0.0, 1.0);
    } else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        camera_position += glm::vec3 (-1.0, 0.0, 0.0);
    }else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        camera_position += glm::vec3(1.0, 0.0, 0.0);
    }else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        camera_position += glm::vec3(0.0, 1.0, 0.0);
    }
}