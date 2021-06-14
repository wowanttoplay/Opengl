//
// Created by virgil on 2021/6/14.
//
#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>

#include "../Shader.h"

class MirrorProcess {
public:
    GLuint color_cube_map_; //生成颜色cube
    GLuint color_FBO;   //  颜色帧缓冲

    MirrorProcess();
    void FirstRender(Shader &shader);
    void SecondRender(Shader &shader);

    void SetNearAndFar(int near, int far);
    void SetCenter(const glm::vec3& center);
    void ConfigShaderAndMatrix(Shader& shader);

    void PrePareResource(GLuint& FBO, GLuint& texture);

private:
    GLuint screen_width_, screen_height_; // 屏幕大小
    float near_, far_;
    glm::vec3 center_; // cube map 生成时的中心位置

};

