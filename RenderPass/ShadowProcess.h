//
// Created by virgil on 2021/6/13.
//
#pragma once
#include <functional>
#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>

#include "../Shader.h"

using FuncOfShadow = std::function<void(glm::mat4, glm::mat4)>;

class ShadowProcess {
public:
    GLuint depth_cube_map_; // 生成的深度cube图
    GLuint depth_map_FBO_;
    ShadowProcess();
    void Render(FuncOfShadow render_func);
    void SetNearAndFar(float near, float far);
    void SetLightPosition(const glm::vec3 light_position);

    void PrePareResource(unsigned int& FBO, unsigned int& texture);
private:

    float near_, far_;  // 视锥体的近、远平面
    glm::vec3 light_position_; // 光源位置
};

