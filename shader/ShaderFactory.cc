//
// Created by virgil on 2021/5/27.
//

#include "ShaderFactory.h"

using namespace std;

void CheckComplie(uint32_t shader) {
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetShaderInfoLog(shader,512, NULL, info_log);
        cout << "COMPILE SHADER IS ERROR " << info_log << endl;
    }
}

void CheckProgram(uint32_t program) {
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char  info_log[512];
        glGetProgramInfoLog(program, 512, NULL, info_log);
        cout << "LINK FAILED, ERR : " << info_log << endl;
    }
}

uint32_t ShaderFactory::CreateVertexShader(const char *vertex_shader_source) {
    if (!vertex_shader_source) return -1;
    uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    CheckComplie(vertex_shader);
    return vertex_shader;
}

uint32_t ShaderFactory::CreateFragmentShader(const char *fragment_shader_source) {
    if (!fragment_shader_source) return -1;
    uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    CheckComplie(fragment_shader);
    return fragment_shader;
}

void ShaderFactory::DestroyProgram(uint32_t program) {
    glDeleteProgram(program);
}

uint32_t ShaderFactory::CreateProgram(uint32_t size, ...) {
    uint32_t program = glCreateProgram();
    if (size < 2) return program;

    // attach shader
    va_list args;
    va_start(args, size);
    for (int i = 0; i < size; ++i) {
        glAttachShader(program, va_arg(args, uint32_t));
    }
    va_end(args);

    glLinkProgram(program);
    CheckProgram(program);
    return program;
}

void ShaderFactory::DestroyShader(uint32_t num, ...) {
    if (num < 1) {
        return;
    }

    va_list args;
    va_start(args, num);
    for (int i = 0;i < num; ++i) {
        glDeleteShader(va_arg(args, uint32_t));
    }
    va_end(args);
}
