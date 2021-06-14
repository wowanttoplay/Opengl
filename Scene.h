//
// Created by virgil on 2021/6/10.
//

#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <vector>
#include "Shader.h"

class Plane;
class Box;
class Sphere;
class ShadowProcess;

class Scene {
public:
    glm::vec3 camera_position;
    glm::vec3 looked_position;
    glm::vec3 looked_direction;

    float scene_width;
    float scene_height;
    float view_angle = 45.0f;

    virtual ~Scene();

    void process_key(int key, int action);

    void SetView(float width, float height);
    void Render();
    void Init();
    void Update(float dt);
private:
    std::shared_ptr<Plane> plane = nullptr;
    std::vector<std::shared_ptr<Box>> box_vec;
    std::shared_ptr<Sphere>light = nullptr;
    std::shared_ptr<Sphere>refract_sphere = nullptr; //表现折射的球
    std::shared_ptr<Sphere> reflect_sphere = nullptr; //表现反射的球

    std::shared_ptr<ShadowProcess> shadow_pass_; // 阴影渲染

    void RenderPlane(Shader &shadow_texture_light);

    void RenderBox(Shader &shadow_texture_light);

    void InitMatrix(Shader &shadow_texture_light) const;

    void RenderLight();

    void RenderRefractSphere(Shader &shadow_texture_light);

    void RenderReflectSphere(Shader &shadow_texture_light);
};

