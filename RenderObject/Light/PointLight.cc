//
// Created by virgil on 2021/11/27.
//

#include "PointLight.h"
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

void PointLight::setTarget(const glm::vec3 &target) {
    target_ = target;
    view_matrix_ = glm::lookAt(getPosition(), target_, glm::vec3(0.0, 1.0, 0.0));
    projection_matrix_ = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f);
}




