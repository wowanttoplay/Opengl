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

Plane* plane = nullptr;
Box* box = nullptr;
Sphere* light = nullptr;


const std::string kFloorName = "floor";
const std::string kBoxName = "Wall";
const std::string kSphereName = "Sphere";
glm::vec3 box_position = glm::vec3(-5.0f, 0.0f, 0.0f);
// light
glm::vec3 light_position = glm::vec3(3.0f, 3.0f, 0.0f);
glm::vec4 light_color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
float light_constant = 1.0f, light_linear = 0.0f, light_quadratic = 0.032f;


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
    // init light resource
    ResourceManager::LoadShader("../Data/Sphere.vs", "../Data/Sphere.fs", nullptr, kSphereName);

    plane = new Plane();
    box = new Box();
    light = new Sphere(30,30);
    light->SetColor(light_color);
}

void Scene::Render() {

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(camera_position, looked_position, glm::vec3(0,1,0));
    glm::mat4 projection = glm::perspective(view_angle, scene_width/scene_height, 0.1f, 100.f);

    // render plane
    Shader floor_shader = ResourceManager::GetShader(kFloorName);
    floor_shader.Use();
    floor_shader.SetVector3f("light.position", light_position);
    floor_shader.SetVector3f("light.color", light_color);
    floor_shader.SetFloat("light.constant", light_constant);
    floor_shader.SetFloat("light.linear", light_linear);
    floor_shader.SetFloat("light.quadratic", light_quadratic);
    floor_shader.SetVector3f("cameraPosition", camera_position);
    plane->Render(ResourceManager::GetShader(kFloorName), ResourceManager::GetTexture(kFloorName), model, view, projection);
    // render box
    glm::mat4 box_model = glm::mat4(1.0f);
    box_model = glm::translate(box_model, box_position);
    box_model = glm::scale(box_model, glm::vec3(7.0f));
    Shader box_shader = ResourceManager::GetShader(kBoxName);
    box_shader.Use();
    box_shader.SetVector3f("light.position", light_position);
    box_shader.SetVector3f("light.color", light_color);
    box_shader.SetFloat("light.constant", light_constant);
    box_shader.SetFloat("light.linear", light_linear);
    box_shader.SetFloat("light.quadratic", light_quadratic);
    box_shader.SetVector3f("cameraPosition", camera_position);
    box->Render(ResourceManager::GetShader(kBoxName), ResourceManager::GetTexture(kBoxName), model, view, projection);
    // render light
    glm::mat4 light_model = glm::mat4(1.0);
    light_model = glm::translate(light_model, light_position);
    light_model = glm::scale(light_model, glm::vec3(0.3f));
    light->Render(ResourceManager::GetShader(kSphereName), ResourceManager::GetTexture(kSphereName), light_model, view, projection);

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
