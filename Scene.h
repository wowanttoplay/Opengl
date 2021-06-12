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

class Plane;
class Box;
class Sphere;

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

};

