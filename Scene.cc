//
// Created by virgil on 2021/6/10.
//

#include "Scene.h"
#include "ResourceManager.h"
#include "RenderObject/Plane.h"
#include "RenderObject/Box.h"

#include "Log/LogUtil.h"
#include "Tool/PrintTool.h"

Plane* plane = nullptr;
Box* box = nullptr;


const std::string kFloorName = "floor";
const std::string kBoxName = "Wall";
glm::vec3 box_position = glm::vec3(-5.0f, 0.0f, 0.0f);


Scene::~Scene() {
    delete plane;
    plane = nullptr;

    delete box;
    box = nullptr;
}


void Scene::Init() {
    camera_position = glm::vec3 (2.0f, 5.0f, 5.0f);
    looked_direction = glm::vec3(0, -5, -3);
    looked_position = camera_position + looked_direction;

    // init plane resource
    ResourceManager::LoadTexture("../Data/Wall.jpeg", kFloorName);
    ResourceManager::LoadShader("../Data/plane.vs", "../Data/plane.fs", nullptr, kFloorName);
    // init box resource
    ResourceManager::LoadTexture("../Data/floor.jpg", kBoxName);
    ResourceManager::LoadShader("../Data/box.vs", "../Data/box.fs", nullptr, kBoxName);

    plane = new Plane();
    box = new Box();
}

void Scene::Render() {

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(camera_position, looked_position, glm::vec3(0,1,0));
    glm::mat4 projection = glm::perspective(view_angle, scene_width/scene_height, 0.1f, 100.f);

    // render plane
    plane->Render(ResourceManager::GetShader(kFloorName), ResourceManager::GetTexture(kFloorName), model, view, projection);
    // render box
    glm::mat4 box_model = glm::mat4(1.0f);
    box_model = glm::translate(box_model, box_position);
    box_model = glm::scale(box_model, glm::vec3(7.0f));
    box->Render(ResourceManager::GetShader(kBoxName), ResourceManager::GetTexture(kBoxName), model, view, projection);
    // render fire

}

void Scene::SetView(float width, float height) {
    scene_width = width;
    scene_height = height;
}

void Scene::Update(float dt) {
    plane->Update(dt);
    looked_position = camera_position + looked_direction;
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
    }else if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        looked_direction += glm::vec3(-1.0, 0.0, 0.0);
    } else if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        looked_direction += glm::vec3(1.0, 0.0, 0.0);
    }else if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
        camera_position += glm::vec3(0, 1, 0);
    }else if (key == GLFW_KEY_X && action == GLFW_PRESS) {
        camera_position += glm::vec3(0, -1, 0);
    }else if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        looked_direction += glm::vec3(0,1,0);
    }else if (key == GLFW_KEY_V && action == GLFW_PRESS) {
        looked_direction += glm::vec3(0,-1,0);
    }

    logE("printf camara info");
    tool::Print(camera_position);
    tool::Print(looked_direction);
}
