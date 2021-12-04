//
// Created by virgil on 2021/6/10.
//

#pragma once
#include <glew.h>
#include <memory>
#include "BaseObject.h"
#include <glm/glm.hpp>

class Texture2D;
class Plane : public BaseObject {
public:
    Plane(std::shared_ptr<Scene> scene, const glm::vec3& scale, const glm::vec3& position);
    ~Plane() override;
    void drawDepthMap(const glm::mat4 &view, const glm::mat4 &projection) override;
    void draw() override;
    void update() override;
    void drawTexture(std::shared_ptr<Texture2D> texture);
    void drawGBuffer(const glm::mat4 &view, const glm::mat4 &projection) override;
private:
    /*
     * 构造VAO
     */
    void constructGeometry();
    uint32_t VAO_,VBO_;

    void simpleColorDraw();

    void drawShadowPhong();

    void drawSimplePhong();
};


