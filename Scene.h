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
    explicit Scene(uint32_t width, uint32_t height);
    virtual ~Scene();
    void process_key(int key, int action);
    void Draw();
    void Init();
    void Update(float dt);
private:
    glm::vec3 camera_position_;
    glm::vec3 looked_direction_;
    glm::vec3 looked_position_;

    uint32_t width_ = 0, height_ = 0; // viewport 大小
};

