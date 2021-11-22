//
// Created by virgil on 2021/11/22.
//

#include "BaseObject.h"
using namespace std;

BaseObject::BaseObject(ObjectType type, weak_ptr<Scene> scene) : type_(type), scene_ptr_(scene) {}
