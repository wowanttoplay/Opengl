//
// Created by virgil on 2021/12/4.
//

#pragma once
#include "Shader.h"
#include "RenderObject/BaseObject.h"

class ShaderTool {
public:
    static bool bindSimpleColorShader(std::shared_ptr<BaseObject> object);
};

