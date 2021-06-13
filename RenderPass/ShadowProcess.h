//
// Created by virgil on 2021/6/13.
//
#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>

#include "../Shader.h"

class ShadowProcess {
public:
    ShadowProcess();
    void FirstRender();
    void SecondRender();
    void SetScreenSize(int width, int height);
    void SetNearAndFar(float near, float far);
    void SetLightPosition(const glm::vec3 light_position);
private:
    GLuint depth_map_FBO_;
    GLuint depth_cube_texture_;
    Shader shader_;
    uint32_t width_, height_;   //屏幕大小，生成阴影贴图时会改变viewport，需要重新设置回来
    float near_, far_;  // 视锥体的近、远平面
    glm::vec3 light_position_; // 光源位置

    void ConfigShaderAndMatrix();

};

