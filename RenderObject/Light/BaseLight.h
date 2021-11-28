//
// Created by virgil on 2021/11/26.
//

#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "../BaseObject.h"

class BaseLight : public BaseObject{
public:
    BaseLight(std::shared_ptr<Scene>scene, const glm::vec3& scale, const glm::vec3& position, const ObjectType& type);
    ~BaseLight() override;

    const glm::mat4 &getViewMatrix() const;

    const glm::mat4 &getProjectionMatrix() const;

protected:
    // 从光源看向场景的矩阵
    glm::mat4 view_matrix_;
    glm::mat4 projection_matrix_;
};


