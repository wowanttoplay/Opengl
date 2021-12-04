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
    void drawDepthMap(const glm::mat4 &view, const glm::mat4 &projection) override;
    void draw() override;
    void update() override;
    void drawGBuffer(const glm::mat4 &view, const glm::mat4 &projection) override;
private:
    void constructGeometry();
private:
    uint32_t VAO_, VBO_;

    void simpleColorDraw();

    void drawSimplePhong();

    void drawShadowPhong();
};


