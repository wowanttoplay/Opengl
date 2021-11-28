//
// Created by virgil on 2021/11/26.
//
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

