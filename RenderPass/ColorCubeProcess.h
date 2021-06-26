//
// Created by virgil on 2021/6/14.
//
#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <functional>

#include "../Shader.h"



class ColorCubeProcess {
    using RenderFunc = std::function<void(glm::mat4 , glm::mat4)>;
public:
    GLuint color_cube_map_; //生成颜色cube
    GLuint color_FBO;   //  颜色帧缓冲

    ColorCubeProcess();
    void FirstRender(Shader &shader);
    void SecondRender(Shader &shader);

    void SetNearAndFar(float near, float far);
    void SetCenter(const glm::vec3& center);
    void ConfigShaderAndMatrix(Shader& shader);

    void SetScreenSize(int width, int height);

    void PrePareResource(GLuint& FBO, GLuint& texture);

    void Render(RenderFunc render_func);

private:
    float screen_width_, screen_height_; // 屏幕大小
    float near_, far_;
    glm::vec3 center_; // cube map 生成时的中心位置

};

