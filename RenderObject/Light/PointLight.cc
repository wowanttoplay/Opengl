//
// Created by virgil on 2021/11/27.
//

#include "PointLight.h"
#include "BaseLight.h"
#include <glog/logging.h>
#include <glm/gtx/transform.hpp>

PointLight::PointLight(std::shared_ptr<Scene> scene, const glm::vec3 &scale, const glm::vec3 &position) : BaseLight(
        scene, scale, position, ObjectType::PointLight) {
    LOG(WARNING) << "PointLight(), ptr : " << this;
}

PointLight::~PointLight() {
    LOG(WARNING) << "~PointLight(), ptr : " << this;
}

void PointLight::draw() {
    if (!object_) {
       object_ = std::make_shared<Sphere>(getScene(), getScale(), getPosition(), 20, 20);
       object_->setColor(getColor());
    }
    object_->drawSimpleColor();
}

void PointLight::update() {

}




