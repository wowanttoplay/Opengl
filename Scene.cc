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
#include "RenderPass/ColorCubeProcess.h"

using namespace std;

const uint32_t box_num = 2;
const std::string kFloorName = "floor";

const std::string kBoxName = "Wall";
const std::string kLight = "Sphere";
const std::string kGlassTextureName = "glass";
const std::string kTextureLightShaderName = "texture_light"; //考虑了纹理与光照的shader
const std::string kShadowShaderName = "shadow";
const std::string kShadowTextureLightShaderName = "shadow_texture_light"; // 考虑了阴影、 纹理、光照的shader
const std::string kColorCubeRenderName = "fbo_cube_color"; // 一个用于生成cube color 的着色器

// projection
const float near_plane = 0.1f, far_plane = 100.f;
//box
glm::vec3 box_position = glm::vec3(0.0f, 0.0f, 0.0f);
// refract sphere
glm::vec3 refract_sphere_position = glm::vec3(2.0f, 2.0f, -1.0f);
// reflect sphere
glm::vec3 reflect_sphere_position = glm::vec3(-2.0f, 1.0f, -2.5f);
// light
const glm::vec3 light_center = glm::vec3(0.0f, 7.0f, 0.0f);;
glm::vec3 light_position = light_center;
const glm::vec3 light_base_color = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 light_color = light_base_color;
float light_constant = 1.0f, light_linear = 0.045f, light_quadratic = 0.0075f;
const float light_move_radius = 5.0f;
//shadow
const float kShadowFarPlane = 120.0f;

Scene::~Scene() {
}


void Scene::Init() {
    camera_position = glm::vec3(2.0f, 5.0f, 5.0f);
    looked_direction = glm::vec3(0, -5, -3);
    looked_position = camera_position + looked_direction;

    // init plane resource
    ResourceManager::LoadTexture("../Data/Wall.jpeg", kFloorName);
    ResourceManager::LoadTexture("../Data/glass.jpeg", kGlassTextureName);
    // init box resource
    ResourceManager::LoadTexture("../Data/floor.jpg", kBoxName);
    // init light resource
    ResourceManager::LoadShader("../Data/Sphere.vs", "../Data/Sphere.fs", nullptr, kLight);
    // init shadow resource
    ResourceManager::LoadShader("../Data/shadow_cube_map.vs", "../Data/shadow_cube_map.fs",
                                nullptr,
                                kShadowShaderName);
    // init shadow render
    Shader shadow_texture_light = ResourceManager::LoadShader("../Data/shadow_texture_light.vs",
                                                              "../Data/shadow_texture_light.fs", nullptr,
                                                              kShadowTextureLightShaderName);
    shadow_texture_light.Use();
    shadow_texture_light.SetInteger("texture0", 0);
    shadow_texture_light.SetInteger("depth_texture", 1);
    shadow_texture_light.SetInteger("reflect_cube_map", 2);
    shadow_texture_light.SetInteger("refract_cube_map", 3);
    shadow_texture_light.SetFloat("far_plane", kShadowFarPlane);
    shadow_texture_light.SetInteger("b_reflected", false);
    shadow_texture_light.SetInteger("b_refracted", false);

    // init color cube render,用与渲染带有阴影的cube颜色缓冲
    Shader color_cube_render = ResourceManager::LoadShader("../Data/color_cube_map.vs",
                                                           "../Data/color_cube_map.fs", "../Data/color_cube_map.gs",
                                                           kColorCubeRenderName);
    color_cube_render.Use();
    color_cube_render.SetInteger("texture0", 0);
    color_cube_render.SetInteger("depth_texture", 1);
//    color_cube_render.SetInteger("color_cube_map", 2);
    color_cube_render.SetFloat("far_plane", kShadowFarPlane);


    plane = std::make_shared<Plane>();
    for (int i = 0; i < box_num; ++i) {
        box_vec.emplace_back(make_shared<Box>());
    }
    light = make_shared<Sphere>(20, 20);
    refract_sphere = make_shared<Sphere>(30, 30);
    reflect_sphere = make_shared<Sphere>(30, 30);

    // 渲染pass
    this->shadow_pass_ = make_shared<ShadowProcess>();
    this->shadow_pass_->SetNearAndFar(0.1f, kShadowFarPlane);

    this->reflect_cube_pass_ = make_shared<ColorCubeProcess>();
    this->reflect_cube_pass_->SetNearAndFar(0.1f, 100.f);
    this->reflect_cube_pass_->SetScreenSize(this->scene_width, this->scene_height);

    this->refract_cube_pass_ = make_shared<ColorCubeProcess>();
    this->refract_cube_pass_->SetNearAndFar(0.1f, 100.f);
    this->refract_cube_pass_->SetScreenSize(this->scene_width, this->scene_height);
}

void Scene::Render() {
    // 为了统一所有的渲染，cube的绘制不再使用gs，而是绘制6次来完成,否则随着效果与元素的增加，都得加一个gs，不方便写
    // 准备阴影贴图
    this->shadow_pass_->Render([=](glm::mat4 view, glm::mat4 projection) -> void {
        Shader shadow_map_shader = ResourceManager::GetShader(kShadowShaderName);
        shadow_map_shader.SetVector3f("light_position", light_position);
        shadow_map_shader.SetFloat("far_plane", kShadowFarPlane);
        this->RenderPlane(shadow_map_shader, view, projection);
        this->RenderBox(shadow_map_shader, view, projection);
//        this->RenderRefractSphere(shadow_map_shader, view, projection);
        this->RenderReflectSphere(shadow_map_shader, view, projection);
    });

//    //反射所需的cube纹理
    this->reflect_cube_pass_->SetCenter(reflect_sphere_position);
    this->reflect_cube_pass_->Render([=](glm::mat4 view, glm::mat4 projection) -> void {
        Shader shadow_texture_light = ResourceManager::GetShader(kShadowTextureLightShaderName);
        shadow_texture_light.Use();
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->shadow_pass_->depth_cube_map_);
        RenderPlane(shadow_texture_light, view, projection);
        RenderBox(shadow_texture_light, view, projection);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->refract_cube_pass_->color_cube_map_);
        shadow_texture_light.SetInteger("b_refracted", true);
        RenderRefractSphere(shadow_texture_light, view, projection);
        shadow_texture_light.SetInteger("b_refracted", false);
        RenderLight(view, projection);
    });
    // 折射所需要的纹理
    this->refract_cube_pass_->SetCenter(refract_sphere_position);
    this->refract_cube_pass_->Render([=](glm::mat4 view, glm::mat4 projection) -> void {
        Shader shadow_texture_light = ResourceManager::GetShader(kShadowTextureLightShaderName);
        shadow_texture_light.Use();
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->shadow_pass_->depth_cube_map_);
        RenderPlane(shadow_texture_light, view, projection);
        RenderBox(shadow_texture_light, view, projection);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->reflect_cube_pass_->color_cube_map_);
        shadow_texture_light.SetInteger("b_reflected", true);
        RenderReflectSphere(shadow_texture_light, view, projection);
        shadow_texture_light.SetInteger("b_reflected", false);
        RenderLight(view, projection);
    });

    //正常渲染
    if (true) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, scene_width, scene_height);
        glClearColor(0.1, 0.1, 0.1, 0.1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::lookAt(camera_position, looked_position, glm::vec3(0, 1, 0));
        glm::mat4 projection = glm::perspective(view_angle, scene_width / scene_height, 0.1f, 100.0f);
        Shader shadow_texture_light = ResourceManager::GetShader(kShadowTextureLightShaderName);
        shadow_texture_light.Use();

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->shadow_pass_->depth_cube_map_);
        // render plane
        RenderPlane(shadow_texture_light, view, projection);
        //render box
        RenderBox(shadow_texture_light, view, projection);
        // render sphere
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->reflect_cube_pass_->color_cube_map_);
        shadow_texture_light.SetInteger("b_reflected", true);
        RenderReflectSphere(shadow_texture_light, view, projection);
        shadow_texture_light.SetInteger("b_reflected", false);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->refract_cube_pass_->color_cube_map_);
        shadow_texture_light.SetInteger("b_refracted", true);
        RenderRefractSphere(shadow_texture_light, view, projection);
        shadow_texture_light.SetInteger("b_refracted", false);
        // render light
        RenderLight(view, projection);
    }

}

void Scene::RenderReflectSphere(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection) {
    glActiveTexture(GL_TEXTURE0);
    ResourceManager::GetTexture(kGlassTextureName).Bind();
    glm::mat4 refract_sphere_model = glm::mat4(1.0f);
    refract_sphere_model = glm::translate(refract_sphere_model, reflect_sphere_position);
    shader.SetMatrix4("model", refract_sphere_model);
    refract_sphere->Render(shader);
}

void Scene::RenderRefractSphere(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection) {
    glActiveTexture(GL_TEXTURE0);
    ResourceManager::GetTexture(kGlassTextureName).Bind();
    glm::mat4 refract_sphere_model = glm::mat4(1.0f);
    refract_sphere_model = glm::translate(refract_sphere_model, refract_sphere_position);
    shader.SetMatrix4("model", refract_sphere_model);
    refract_sphere->Render(shader);
}

void Scene::RenderLight(const glm::mat4 &view, const glm::mat4 &projection) {
    Shader light_shader = ResourceManager::GetShader(kLight);
    light_shader.Use();
    glm::mat4 light_model = glm::mat4(1.0);
    light_model = glm::translate(light_model, light_position);
    light_model = glm::scale(light_model, glm::vec3(0.5f));
    light_shader.SetMatrix4("model", light_model);
    light_shader.SetMatrix4("view", view);
    light_shader.SetMatrix4("projection", projection);
    light->Render(light_shader);
}

void Scene::RenderBox(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection) {// box
    shader.Use();
    shader.SetMatrix4("projection", projection);
    shader.SetMatrix4("view", view);
    glActiveTexture(GL_TEXTURE0);
    ResourceManager::GetTexture(kBoxName).Bind();
    for (int i = 0; i < box_num; ++i) {
        glm::mat4 box_model = glm::mat4(1.0f);
        box_model = glm::translate(box_model, box_position + glm::vec3(i * 1.1, 0, -i * 1.3));
        box_model = glm::scale(box_model, glm::vec3(1.0f, 1.5f, 1.0f));
        shader.SetMatrix4("model", box_model);
        box_vec.at(i)->Render(shader);
    }
}

void Scene::RenderPlane(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection) {//plane
    shader.Use();
    shader.SetMatrix4("projection", projection);
    shader.SetMatrix4("view", view);
    glActiveTexture(GL_TEXTURE0);
    ResourceManager::GetTexture(kFloorName).Bind();
    glm::mat4 plane_model = glm::mat4(1.0f);
    shader.SetMatrix4("model", plane_model);
    plane->Render(shader);
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
    light_position = light_center + glm::vec3(sin(dt / 3) * light_move_radius, 0, cos(dt / 3) * light_move_radius);
//    light_color = light_base_color + glm::vec3(0, -sin(dt)*0.8, -cos(dt)*0.8);
    Shader light_shader = ResourceManager::GetShader(kLight);
    light_shader.Use();
    light_shader.SetVector3f("color", light_color);

    // 更新渲染的相关属性
    plane->Update(dt);
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
    shadow_texture_light.SetVector3f("cameraPosition", camera_position);
    // 设置color cube的着色器,因为要一次渲染6个面，所以需要单独写一个着色器
    Shader color_cube_shader = ResourceManager::GetShader(kColorCubeRenderName);
    color_cube_shader.Use();
    color_cube_shader.SetVector3f("light.position", light_position);
    color_cube_shader.SetVector3f("light.color", light_color);
    color_cube_shader.SetFloat("light.constant", light_constant);
    color_cube_shader.SetFloat("light.linear", light_linear);
    color_cube_shader.SetFloat("light.quadratic", light_quadratic);
    color_cube_shader.SetVector3f("cameraPosition", camera_position);
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
