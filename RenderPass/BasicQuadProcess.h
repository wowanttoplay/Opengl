//
// Created by virgil on 2021/7/11.
//

#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <functional>
#include "../Texture2D.h"


class BasicQuadProcess {
public:
    using RenderFunc = std::function<void()>;
    BasicQuadProcess(float width, float height);
    void Render(RenderFunc render_func);
    Texture2D texture_;
private:
    void InitFBO();
    GLuint FBO_;
    float width_ = 1024, height_ = 1024;
};
