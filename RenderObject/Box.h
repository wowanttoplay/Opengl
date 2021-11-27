//
// Created by virgil on 2021/6/11.
//


#pragma once
#include <glew.h>
#include <glm/glm.hpp>
#include <memory>
#include "BaseObject.h"


class Box : public BaseObject {
public:
    Box(std::shared_ptr<Scene> scene, const glm::vec3& scale, const glm::vec3& position);
    ~Box() override;
    void drawShadow() override;
    void draw() override;
    void update() override;

private:
    void constructGeometry();
private:
    uint32_t VAO_, VBO_;

    void simpleColorDraw();
};


