//
// Created by virgil on 2021/6/10.
//

#pragma once
#include <glew.h>
#include "../Shader.h"
#include "../Texture2D.h"


class Plane {
public:
    Plane();
    uint32_t VAO,VBO;
    void Render(Shader shader);
    void Update(float dt);
};


