//
// Created by virgil on 2021/11/26.
//
#include <glm/gtx/transform.hpp>
#include "PointLight.h"
#include <glog/logging.h>
#include <glm/gtx/string_cast.hpp>
#include "BaseLight.h"
#include "../BaseObject.h"

using namespace std;
using namespace google;

BaseLight::BaseLight(std::shared_ptr<Scene> scene, const glm::vec3 &scale, const glm::vec3 &position, const ObjectType& type)
: BaseObject(type, scene, scale, position)
{
    LOG(WARNING) << "BaseLight(), ptr : " << this;
}

BaseLight::~BaseLight() {
    LOG(WARNING) << "BaseLight(), ptr : " << this;
}

const glm::mat4 &BaseLight::getViewMatrix() const {
    return view_matrix_;
}

const glm::mat4 &BaseLight::getProjectionMatrix() const {
    return projection_matrix_;
}

float BaseLight::getNearPlane() const {
    return near_plane_;
}

float BaseLight::getFarPlane() const {
    return far_plane_;
}

void BaseLight::setTarget(const glm::vec3 &target) {
    target_ = target;
    view_matrix_ = glm::lookAt(getPosition(), target_, glm::vec3(0.0, 1.0, 0.0));
    projection_matrix_ = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
}

void BaseLight::setFarPlane(float farPlane) {
    far_plane_ = farPlane;
}

void BaseLight::setNearPlane(float nearPlane) {
    near_plane_ = nearPlane;
}
