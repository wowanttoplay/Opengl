//
// Created by virgil on 2021/6/10.
//

#pragma once
#include <glew.h>
#include <memory>
#include "BaseObject.h"
#include "../Shader.h"
#include "../Texture2D.h"


class Plane : public BaseObject {
public:
    Plane(std::weak_ptr<Scene> scene);
    virtual ~Plane() override;
    void DrawShadow() override;
    void Draw() override;
    void Update(float dt) override;
private:
    uint32_t VAO,VBO;
};


