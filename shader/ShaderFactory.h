//
// Created by virgil on 2021/5/27.
//
#pragma once

#include <glew.h>
#include <glfw3.h>
#include <iostream>


class ShaderFactory {

public:
    static uint32_t CreateVertexShader(const char *vertex_shader_source);

    static void DestroyShader(uint32_t num, ...);

    static uint32_t CreateFragmentShader(const char *fragment_shader_source);

    static uint32_t CreateProgram(uint32_t size, ...);

    static void DestroyProgram(uint32_t program);

};

