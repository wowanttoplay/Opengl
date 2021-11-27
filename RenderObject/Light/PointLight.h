//
// Created by virgil on 2021/11/27.
//
#pragma once
#include <memory>
#include "BaseLight.h"
#include "../Sphere.h"

class PointLight : public BaseLight{
public:
    PointLight(std::shared_ptr<Scene> scene, const glm::vec3& scale, const glm::vec3& position);
    ~PointLight() override;

    void draw() override;

    void update() override;
private:
    std::shared_ptr<Sphere> object_ = nullptr; // 用来绘制的实体
};


