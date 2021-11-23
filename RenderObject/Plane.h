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
    Plane(std::shared_ptr<Scene> scene, const glm::vec3& size, const glm::vec3& center);
    ~Plane() override;
    void DrawShadow() override;
    void Draw() override;
    void Update(float dt) override;
private:
    /*
     * 构造VAO
     */
    void ConstructGeometry();
    uint32_t VAO_,VBO_;
    glm::vec3 size_; // 形状大小
    glm::vec3 center_; // 中心点
    glm::mat4 model_; // model矩阵
};


