//
// Created by virgil on 2021/6/11.
//


#pragma once
#include <glew.h>
#include "../Texture2D.h"
#include "../Shader.h"
#include "../ResourceManager.h"

class Box {
public:
    uint32_t VAO, VBO;
    Box();
    void Render(Shader shader);
};


