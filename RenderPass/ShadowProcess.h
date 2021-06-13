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
    GLuint depth_cube_texture_; // 生成的深度cube图
    GLuint depth_map_FBO_;
    ShadowProcess();
    void FirstRender(Shader shader);
    void SecondRender();
    void SetScreenSize(int width, int height);
    void SetNearAndFar(float near, float far);
    void SetLightPosition(const glm::vec3 light_position);
    void ConfigShaderAndMatrix(Shader shader);

    void PrePareResource(unsigned int& FBO, unsigned int& texture);
private:

    uint32_t screen_width_, screen_height_;   //屏幕大小，生成阴影贴图时会改变viewport，需要重新设置回来
    float near_, far_;  // 视锥体的近、远平面
    glm::vec3 light_position_; // 光源位置



};

