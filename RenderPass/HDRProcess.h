//
// Created by virgil on 2021/6/20.
//

#pragma once

#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <functional>

class HDRProcess {
public:
    using RenderFunc = std::function<void()>;
    GLuint FBO_, texture_;
    GLuint VAO_, VBO_;

    HDRProcess();

    void PreRender(RenderFunc render_func);

    void SecondRender();

    void InitFBO();

    void InitVAO();
    // 设置gamma值
    void SetGamma(float gamma);
    inline float Getgamma() {return gamma_;}

    // 设置曝光值
    void SetExposure(float exposure);
    inline float GetExposure() {return exposure_;}

private:
    float gamma_ = 2.2f;
    float exposure_ = 0.05f;
};

