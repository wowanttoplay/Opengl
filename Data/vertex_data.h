//
// Created by virgil on 2021/5/25.
//

#pragma once

#include <glew.h>
#include <glfw3.h>

using namespace std;

namespace RenderData {

    GLfloat triangle_vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };

    GLfloat square_vertices[] = {
            // 第一个三角形
            0.5f, 0.5f, 0.0f,   // 右上角
            0.5f, -0.5f, 0.0f,  // 右下角
            -0.5f, 0.5f, 0.0f,  // 左上角
            // 第二个三角形
            0.5f, -0.5f, 0.0f,  // 右下角
            -0.5f, -0.5f, 0.0f, // 左下角
            -0.5f, 0.5f, 0.0f   // 左上角
    };

    GLfloat square_element_vertices[] = {
            0.5f, 0.5f, 0.0f,   // 右上角
            0.5f, -0.5f, 0.0f,  // 右下角
            -0.5f, -0.5f, 0.0f, // 左下角
            -0.5f, 0.5f, 0.0f   // 左上角
    };

    uint32_t square_element_indices[] = {
            0, 1, 3, // 第一个三角形
            1, 2, 3  // 第二个三角形
    };

    GLfloat color_triangle_vertices[] = {
            // 位置              // 颜色
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // 左下
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // 顶部
    };

    GLfloat square_texture_vertices[] = {
            // 位置                        //纹理坐标
            -0.5f, -0.5f,                0.0f, 0.0f,
            0.5f, -0.5f,                 1.0f, 0.0f,
            0.5f, 0.5f,                  1.0f, 1.0f,

            -0.5f, -0.5f,                0.0f, 0.0f,
            0.5f, 0.5f,                  1.0f, 1.0f,
            -0.5f, 0.5f,                 0.0f, 1.0f,
    };

}


