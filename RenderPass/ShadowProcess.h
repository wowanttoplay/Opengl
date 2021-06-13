//
// Created by virgil on 2021/6/13.
//
#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>

class ShadowProcess {
public:
    ShadowProcess();
private:
    GLuint depth_map_FBO_;
    GLuint depth_cube_texture_;

};

