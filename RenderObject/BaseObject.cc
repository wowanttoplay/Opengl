//
// Created by virgil on 2021/11/22.
//

#include "BaseObject.h"
#include "glog/logging.h"
#include "../Scene.h"
#include <glm/gtx/string_cast.hpp>
using namespace std;
using namespace google;

BaseObject::BaseObject(ObjectType type, std::shared_ptr<Scene> scene, const glm::vec3 &scale, const glm::vec3 &position)
        : type_(type), scene_ptr_(scene), scale_(scale), position_(position) {
    updateModelMatrix();
    LOG(WARNING) << "object (), type :" << static_cast<underlying_type<ObjectType>::type>(type_) << "\tmodel matrix " << glm::to_string(modelMatrix_) << "\t, ptr : " << this;
}

BaseObject::~BaseObject() {
    LOG(WARNING) <<"object ~(), type :" << static_cast<underlying_type<ObjectType>::type>(type_) << ", ptr : " << this;
}

std::shared_ptr<Scene> BaseObject::getScene() {
    return scene_ptr_.lock();
}

void BaseObject::drawDepthMap(const glm::mat4 &view, const glm::mat4 &projection) {

}

const glm::vec3 &BaseObject::getPosition() const {
    return position_;
}

const glm::vec4 &BaseObject::getColor() const {
    return color_;
}

const glm::vec3 &BaseObject::getScale() const {
    return scale_;
}

const glm::mat4 &BaseObject::getModelMatrix() const {
    return modelMatrix_;
}

void BaseObject::setPosition(const glm::vec3 &position) {
    position_ = position;
    updateModelMatrix();
}

void BaseObject::updateModelMatrix() {
    modelMatrix_ = glm::mat4(1.0f);
    modelMatrix_ = glm::translate(modelMatrix_, position_);
    modelMatrix_ = glm::scale(modelMatrix_, scale_);
}

void BaseObject::setScale(const glm::vec3 &scale) {
    scale_ = scale;
    updateModelMatrix();
}
