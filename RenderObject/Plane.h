//
// Created by virgil on 2021/6/10.
//

#pragma once
#include <glew.h>
#include <memory>
#include "BaseObject.h"
#include <glm/glm.hpp>


class Plane : public BaseObject {
public:
    Plane(std::shared_ptr<Scene> scene, const glm::vec3& scale, const glm::vec3& position);
    ~Plane() override;
    void drawShadow() override;
    void draw() override;
    void update() override;
private:
    /*
     * 构造VAO
     */
    void ConstructGeometry();
    uint32_t VAO_,VBO_;

    void SimpleColorDraw();
};


