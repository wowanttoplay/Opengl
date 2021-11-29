//
// Created by virgil on 2021/11/29.
//

#pragma once
#include <glew.h>
#include <memory>
#include <glm/glm.hpp>
#include "../BaseObject.h"

class Texture2D;
class DebugPlane : public BaseObject{
public:
    DebugPlane(std::shared_ptr<Scene> scene);
    ~DebugPlane() override;
    void draw() override;
    void update() override;
    void drawTexture(std::shared_ptr<Texture2D> texture);
private:
    /*
     * 构造VAO
     */
    void constructGeometry();
    uint32_t VAO_,VBO_;
};


