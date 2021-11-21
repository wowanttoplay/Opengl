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

class Scene {
public:
    glm::vec3 camera_position;
    glm::vec3 looked_direction;
    glm::vec3 looked_position;

    virtual ~Scene();
    void process_key(int key, int action);
    void Render();
    void Init();
    void Update(float dt);
private:
};

