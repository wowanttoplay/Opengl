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
#include "RenderPass/ShadowProcess.h"

using namespace std;

const uint32_t box_num = 1;
const std::string kFloorName = "floor";

const std::string kBoxName = "Wall";
const std::string kLight = "Sphere";
const std::string kTextureLightShaderName = "texture_light"; //考虑了纹理与光照的shader
const std::string kShadowShaderName = "shadow";
const std::string kShadowTextureLightShaderName = "shadow_texture_light"; // 考虑了阴影、 纹理、光照的shader

// projection
const float near_plane = 0.1f, far_plane = 100.f;
//box
glm::vec3 box_position = glm::vec3(0.0f, 0.0f, 0.0f);
// light
const glm::vec3 light_center = glm::vec3(0.0f, 30.0f, 0.0f);
const float light_radius = 0.3f;
glm::vec3 light_position = light_center;
const glm::vec3 light_base_color = glm::vec3(3.0f, 3.0f, 3.0f);
glm::vec3 light_color = light_base_color;
float light_constant = 1.0f, light_linear = 0.045f, light_quadratic = 0.0075f;
const float light_move_radius = 10.0f;
//shadow
const float kShadowFarPlane = 100.0f;

Scene::~Scene() {
}


void Scene::Init() {
    camera_position = glm::vec3(2.0f, 5.0f, 5.0f);
    looked_direction = glm::vec3(0, -5, -3);
    looked_position = camera_position + looked_direction;

    // init plane resource
    ResourceManager::LoadTexture("../Data/Wall.jpeg", kFloorName);
    Shader texture_light_shader = ResourceManager::LoadShader("../Data/texture_light.vs", "../Data/texture_light.fs",
                                                              nullptr,
                                                              kTextureLightShaderName);
    texture_light_shader.Use();
    texture_light_shader.SetInteger("texture0", 0);
    // init box resource
    ResourceManager::LoadTexture("../Data/floor.jpg", kBoxName);
    // init light resource
    ResourceManager::LoadShader("../Data/Sphere.vs", "../Data/Sphere.fs", nullptr, kLight);
    // init shadow resource
    ResourceManager::LoadShader("../Data/shadow_map.vs", "../Data/shadow_map.fs",
                                "../Data/shadow_map.gs",
                                kShadowShaderName);
    // init shadow render
    Shader shadow_texture_light = ResourceManager::LoadShader("../Data/shadow_texture_light.vs",
                                                              "../Data/shadow_texture_light.fs", nullptr,
                                                              kShadowTextureLightShaderName);
    shadow_texture_light.Use();
    shadow_texture_light.SetInteger("texture0", 0);
    shadow_texture_light.SetInteger("depth_texture", 1);
    shadow_texture_light.SetFloat("far_plane", kShadowFarPlane);

    plane = std::make_shared<Plane>();
    for (int i = 0; i < box_num; ++i) {
        box_vec.emplace_back(make_shared<Box>());
    }
    light = make_shared<Sphere>(30, 30);

    // 渲染pass
    this->shadow_pass_ = make_shared<ShadowProcess>();
    this->shadow_pass_->SetNearAndFar(0.1f, kShadowFarPlane);
    this->shadow_pass_->SetScreenSize(this->scene_width, this->scene_height);
}

void Scene::Render() {
    // 准备阴影贴图
    Shader shadow_map_shader = ResourceManager::GetShader(kShadowShaderName);
    this->shadow_pass_->FirstRender(shadow_map_shader);
    RenderPlane(shadow_map_shader);
    RenderBox(shadow_map_shader);

    // 正常渲染
    this->shadow_pass_->SecondRender();
    Shader shadow_texture_light = ResourceManager::GetShader(kShadowTextureLightShaderName);
    shadow_texture_light.Use();
    InitMatrix(shadow_texture_light);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->shadow_pass_->depth_cube_texture_);

    RenderPlane(shadow_texture_light);
    RenderBox(shadow_texture_light);
    // light
    RenderLight();
}

void Scene::RenderLight() {
    glm::mat4 view= glm::lookAt(camera_position, looked_position, glm::vec3(0, 1, 0));
    glm::mat4 projection= glm::perspective(view_angle, scene_width / scene_height, 0.1f, 100.0f);
    Shader light_shader = ResourceManager::GetShader(kLight);
    light_shader.Use();
    glm::mat4 light_model = glm::mat4(1.0);
    light_model = glm::translate(light_model, light_position);
    light_model = glm::scale(light_model, glm::vec3(light_radius));
    light_shader.SetMatrix4("model", light_model);
    light_shader.SetMatrix4("view", view);
    light_shader.SetMatrix4("projection", projection);
    light->Render(light_shader);
}

void Scene::InitMatrix(Shader &shadow_texture_light) const {
    glm::mat4 view= glm::lookAt(camera_position, looked_position, glm::vec3(0, 1, 0));
    glm::mat4 projection= glm::perspective(view_angle, scene_width / scene_height, 0.1f, 100.0f);
    shadow_texture_light.SetMatrix4("projection", projection);
    shadow_texture_light.SetMatrix4("view", view);
}

void Scene::RenderBox(Shader &shadow_texture_light) {// box
    glActiveTexture(GL_TEXTURE0);
    ResourceManager::GetTexture(kBoxName).Bind();
    for (int i = 0; i < box_num; ++i) {
        glm::mat4 box_model = glm::mat4(1.0f);
        box_model = glm::translate(box_model, box_position + glm::vec3(i * 1.1, 0, -i * 1.3));
        box_model = glm::scale(box_model, glm::vec3(1.0f,10.0f,1.0f));
        shadow_texture_light.SetMatrix4("model", box_model);
        box_vec.at(i)->Render(shadow_texture_light);
    }
}

void Scene::RenderPlane(Shader &shadow_texture_light) {//plane
    glActiveTexture(GL_TEXTURE0);
    ResourceManager::GetTexture(kFloorName).Bind();
    glm::mat4 plane_model = glm::mat4(1.0f);
    shadow_texture_light.SetMatrix4("model", plane_model);
    plane->Render(shadow_texture_light);
}

void Scene::SetView(float width, float height) {
    this->scene_width = width;
    this->scene_height = height;
    logI("scene width: %f, height :%f", width, height);
}

void Scene::Update(float dt) {
    // 更新相机
    looked_position = camera_position + looked_direction;
    // 更新light的相关属性
    light_position = light_center + glm::vec3(sin(dt/3) * light_move_radius, 0, cos(dt/3) * light_move_radius);
//    light_color = light_base_color + glm::vec3(0, -sin(dt)*0.8, -cos(dt)*0.8);
    Shader light_shader = ResourceManager::GetShader(kLight);
    light_shader.Use();
    light_shader.SetVector3f("color", light_color);

    // 更新渲染的相关属性
    plane->Update(dt);
    Shader texture_light = ResourceManager::GetShader(kTextureLightShaderName);
    texture_light.Use();
    texture_light.SetVector3f("light.position", light_position);
    texture_light.SetVector3f("light.color", light_color);
    texture_light.SetFloat("light.constant", light_constant);
    texture_light.SetFloat("light.linear", light_linear);
    texture_light.SetFloat("light.quadratic", light_quadratic);
    texture_light.SetVector3f("cameraPosition", camera_position);


    // 更新render pass中光源的位置，实时更改shadow map
    this->shadow_pass_->SetLightPosition(light_position);
    // 设置阴影、纹理、光照的着色器
    Shader shadow_texture_light = ResourceManager::GetShader(kShadowTextureLightShaderName);
    shadow_texture_light.Use();

    shadow_texture_light.SetVector3f("light.position", light_position);
    shadow_texture_light.SetVector3f("light.color", light_color);
    shadow_texture_light.SetFloat("light.constant", light_constant);
    shadow_texture_light.SetFloat("light.linear", light_linear);
    shadow_texture_light.SetFloat("light.quadratic", light_quadratic);
    shadow_texture_light.SetFloat("light.radius", light_radius);
    shadow_texture_light.SetVector3f("cameraPosition", camera_position);


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
    } else if (key == GLFW_KEY_B && action == GLFW_PRESS) {
        Shader shadow_texture_light = ResourceManager::GetShader(kShadowTextureLightShaderName);
        shadow_texture_light.Use();
        shadow_texture_light.SetInteger("shadow_type", 0);
    } else if (key == GLFW_KEY_N && action == GLFW_PRESS) {
        Shader shadow_texture_light = ResourceManager::GetShader(kShadowTextureLightShaderName);
        shadow_texture_light.Use();
        shadow_texture_light.SetInteger("shadow_type", 1);
    } else if (key == GLFW_KEY_M && action == GLFW_PRESS) {
        Shader shadow_texture_light = ResourceManager::GetShader(kShadowTextureLightShaderName);
        shadow_texture_light.Use();
        shadow_texture_light.SetInteger("shadow_type", 2);
    }

    logE("printf camara info");
    tool::Print(camera_position);
    tool::Print(looked_direction);
}
