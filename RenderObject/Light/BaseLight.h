//
// Created by virgil on 2021/11/26.
//

#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "../BaseObject.h"
#include "../Sphere.h"

class BaseLight : public BaseObject{
    glm::vec3 target_;
public:
    BaseLight(std::shared_ptr<Scene>scene, const glm::vec3& scale, const glm::vec3& position, const ObjectType& type);
    ~BaseLight() override;

    const glm::mat4 &getViewMatrix() const;

    const glm::mat4 &getProjectionMatrix() const;

    float getNearPlane() const;

    float getFarPlane() const;

    void setTarget(const glm::vec3 &target);

protected:
    // 从光源看向场景的矩阵
    glm::mat4 view_matrix_;
    glm::mat4 projection_matrix_;
    float far_plane_ = 10.0f;
    float near_plane_ = 0.1f;
    float aspect_ = 1.0f;
public:
    void setAspect(float aspect);

public:
    float getAspect() const;

public:
    void setFarPlane(float farPlane);

    void setNearPlane(float nearPlane);

private:
    void updateMatrix();
};


