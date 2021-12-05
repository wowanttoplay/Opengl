//
// Created by virgil on 2021/11/29.
//

#pragma once
#include <glew.h>
#include <memory>
#include <glm/glm.hpp>
#include "../BaseObject.h"

class Texture2D;
enum class DebugType{
    DebugType_Shadow = 0,
    DebugType_RGB = 1,
    DebugType_RGBA = 2,
    DebugType_R = 3,
    DebugType_G = 4,
    DebugType_B = 5,
    DebugType_A  =6
};


class DebugPlane : public BaseObject{
public:
    DebugPlane(std::shared_ptr<Scene> scene);
    ~DebugPlane() override;
    void draw() override;
    void update() override;
    void drawTexture(std::shared_ptr<Texture2D> texture, DebugType type);

    void prepareAOMap();
private:
    /*
     * 构造VAO
     */
    void constructGeometry();
    uint32_t VAO_,VBO_;
};


