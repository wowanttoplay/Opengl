//
// Created by virgil on 2021/11/22.
//
#pragma once
#include <memory>
#include "../Scene.h"

enum class ObjectType{
    PLANE,
    SPHERE,
};

class BaseObject {
public:
    explicit BaseObject(ObjectType type, std::weak_ptr<Scene> scene);

    virtual ~BaseObject();

    /**
     * 绘制shadow map时执行
     */
    virtual void DrawShadow() = 0;

    /**
     * 正常绘制
     */
     virtual void Draw() = 0;

     /**
      * 更新
      * @param dt 统一的当前时间
      */
     virtual void Update(float dt) = 0;

private:
    ObjectType type_;
    std::weak_ptr<Scene> scene_ptr_;
};

