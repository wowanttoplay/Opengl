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
private:
    uint32_t intensity_ = 1;
};


