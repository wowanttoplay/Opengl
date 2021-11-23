//
// Created by virgil on 2021/11/22.
//

#include "BaseObject.h"
#include "glog/logging.h"
#include "../Scene.h"
using namespace std;
using namespace google;

BaseObject::BaseObject(ObjectType type, shared_ptr<Scene> scene) : type_(type), scene_ptr_(scene) {
    LOG(WARNING) <<"object (), type :" << static_cast<underlying_type<ObjectType>::type>(type_) << ", ptr : " << this;
}

BaseObject::~BaseObject() {
    LOG(WARNING) <<"object ~(), type :" << static_cast<underlying_type<ObjectType>::type>(type_) << ", ptr : " << this;
}

std::shared_ptr<Scene> BaseObject::GetScene() {
    return scene_ptr_.lock();
}
