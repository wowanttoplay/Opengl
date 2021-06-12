//
// Created by virgil on 2021/6/10.
//

#include "Scene.h"
#include "ResourceManager.h"
#include "RenderObject/Plane.h"
#include "RenderObject/Box.h"
#include "RenderObject/Sphere.h"

#include "Log/LogUtil.h"
#include "Tool/PrintTool.h"

using namespace std;

const uint32_t box_num = 5;
const std::string kFloorName = "floor";
const std::string kBoxName = "Wall";
const std::string kLight = "Sphere";
glm::vec3 box_position = glm::vec3(0.0f, 0.0f, 0.0f);
// light
const glm::vec3 light_center = glm::vec3(0.0f, 3.0f, 0.0f);;
glm::vec3 light_position = light_center;
const glm::vec3 light_base_color = glm::vec3(1.0f, 0.8f, 0.8f);
glm::vec3 light_color = light_base_color;
float light_constant = 1.0f, light_linear = 0.09f, light_quadratic = 0.032f;
const float light_move_radius = 3.0f;


Scene::~Scene() {
}


void Scene::Init() {
    camera_position = glm::vec3(2.0f, 5.0f, 5.0f);
    looked_direction = glm::vec3(0, -5, -3);
    looked_position = camera_position + looked_direction;

    // init plane resource
    ResourceManager::LoadTexture("../Data/Wall.jpeg", kFloorName);
    ResourceManager::LoadShader("../Data/plane.vs", "../Data/plane.fs", nullptr, kFloorName);
    // init box resource
    ResourceManager::LoadTexture("../Data/floor.jpg", kBoxName);
    ResourceManager::LoadShader("../Data/box.vs", "../Data/box.fs", nullptr, kBoxName);
    // init light resource
    ResourceManager::LoadShader("../Data/Sphere.vs", "../Data/Sphere.fs", nullptr, kLight);

    plane = std::make_shared<Plane>();
    for (int i = 0; i < box_num; ++i) {
        box_vec.emplace_back(make_shared<Box>());
    }
    light = make_shared<Sphere>(30, 30);
}

void Scene::Render() {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(camera_position, looked_position, glm::vec3(0, 1, 0));
    glm::mat4 projection = glm::perspective(view_angle, scene_width / scene_height, 0.1f, 100.f);
//
//    // render plane
    plane->Render(ResourceManager::GetShader(kFloorName), ResourceManager::GetTexture(kFloorName), model, view,
                  projection);
//    // render box
    for (int i = 0; i < box_num; ++i) {
        glm::mat4 box_model = glm::mat4(1.0f);
        box_model = glm::translate(box_model, box_position + glm::vec3(0, 0, -i*2));
        box_model = glm::scale(box_model, glm::vec3(1.0f));
        box_vec.at(i)->Render(ResourceManager::GetShader(kBoxName), ResourceManager::GetTexture(kBoxName), box_model, view, projection);
    }
//    // render light
    glm::mat4 light_model = glm::mat4(1.0);
    light_model = glm::translate(light_model, light_position);
    light_model = glm::scale(light_model, glm::vec3(1.0f));
    light->Render(ResourceManager::GetShader(kLight), ResourceManager::GetTexture(kLight), light_model, view,
                  projection);
}

void Scene::SetView(float width, float height) {
    scene_width = width;
    scene_height = height;
}

void Scene::Update(float dt) {
    // 更新相机
    looked_position = camera_position + looked_direction;
    // 更新light的相关属性
    light_position = light_center + glm::vec3(sin(dt) * light_move_radius, 0, cos(dt) * light_move_radius);
//    light_color = light_base_color + glm::vec3(0, -sin(dt)*0.8, -cos(dt)*0.8);
    Shader light_shader = ResourceManager::GetShader(kLight);
    light_shader.Use();
    light_shader.SetVector3f("color", light_color);

    // 更新地板的相关属性
    plane->Update(dt);
    Shader floor_shader = ResourceManager::GetShader(kFloorName);
    floor_shader.Use();
    floor_shader.SetVector3f("light.position", light_position);
    floor_shader.SetVector3f("light.color", light_color);
    floor_shader.SetFloat("light.constant", light_constant);
    floor_shader.SetFloat("light.linear", light_linear);
    floor_shader.SetFloat("light.quadratic", light_quadratic);
    floor_shader.SetVector3f("cameraPosition", camera_position);
    // 更新box的相关属性
    Shader box_shader = ResourceManager::GetShader(kBoxName);
    box_shader.Use();
    box_shader.SetVector3f("light.position", light_position);
    box_shader.SetVector3f("light.color", light_color);
    box_shader.SetFloat("light.constant", light_constant);
    box_shader.SetFloat("light.linear", light_linear);
    box_shader.SetFloat("light.quadratic", light_quadratic);
    box_shader.SetVector3f("cameraPosition", camera_position);


}

void Scene::process_key(int key, int action) {
    logE("scene, press key : %d", key);
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        camera_position += glm::vec3(0.0, 0.0, -1.0);
    } else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        camera_position += glm::vec3(0.0, 0.0, 1.0);
    } else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        camera_position += glm::vec3(-1.0, 0.0, 0.0);
    } else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        camera_position += glm::vec3(1.0, 0.0, 0.0);
    } else if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        looked_direction += glm::vec3(-1.0, 0.0, 0.0);
    } else if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        looked_direction += glm::vec3(1.0, 0.0, 0.0);
    } else if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
        camera_position += glm::vec3(0, 1, 0);
    } else if (key == GLFW_KEY_X && action == GLFW_PRESS) {
        camera_position += glm::vec3(0, -1, 0);
    } else if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        looked_direction += glm::vec3(0, 1, 0);
    } else if (key == GLFW_KEY_V && action == GLFW_PRESS) {
        looked_direction += glm::vec3(0, -1, 0);
    }

    logE("printf camara info");
    tool::Print(camera_position);
    tool::Print(looked_direction);
}
