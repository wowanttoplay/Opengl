//
// Created by virgil on 2021/11/22.
//

#include "BaseObject.h"
#include "glog/logging.h"
using namespace std;
using namespace google;

BaseObject::BaseObject(ObjectType type, weak_ptr<Scene> scene) : type_(type), scene_ptr_(scene) {
    LOG(WARNING) <<"object (), type :" << static_cast<underlying_type<ObjectType>::type>(type_);
}

BaseObject::~BaseObject() {
    LOG(WARNING) <<"object ~(), type :" << static_cast<underlying_type<ObjectType>::type>(type_);
}
