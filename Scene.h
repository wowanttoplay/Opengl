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
#include "Camera.h"

class Scene {
public:
    explicit Scene(uint32_t width, uint32_t height);
    virtual ~Scene();
    void Draw();
    void Update(float dt);
public:
    // 外部回调
    void ProcessKey(int key, int action);
    void MouseCallBack(double x, double y);
    void MouseScrollCallBack(double x_offset, double y_offset);
private:
    std::shared_ptr<Camera> camera_ = nullptr;
    uint32_t width_ = 0, height_ = 0; // viewport 大小
};

