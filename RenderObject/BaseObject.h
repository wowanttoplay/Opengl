//
// Created by virgil on 2021/11/22.
//
#pragma once

#include <memory>
#include <glm/glm.hpp>


enum class ObjectType {
    Plane,
    Sphere,
    Box,
    Camera,
    PointLight,
    DeubgPlane,
};

class Scene;

class BaseObject : public std::enable_shared_from_this<BaseObject>{
public:
    BaseObject(ObjectType type, std::shared_ptr<Scene> scene, const glm::vec3 &scale, const glm::vec3 &position);

    virtual ~BaseObject();

    /**
     * 绘制shadow map时执行
     */
    virtual void drawDepthMap(const glm::mat4 &view, const glm::mat4 &projection);

    /**
     * 按照给定的矩阵绘制gbuffer
     * @param view
     * @param projection
     */
    virtual void drawGBuffer(const glm::mat4 &view, const glm::mat4 &projection);

    /**
     * 正常绘制
     */
    virtual void draw() = 0;

    /**
     * 更新
     * @param dt 统一的当前时间
     */
    virtual void update() = 0;

    /**
     * 获取scene的智能指针
     * @return scene的智能指针
     */
    std::shared_ptr<Scene> getScene();

    void setColor(const glm::vec4 &color) { color_ = color; }

    const glm::vec4 &getColor() const;

    const glm::mat4 &getModelMatrix() const;

    void setPosition(const glm::vec3 &position);

    const glm::vec3 &getPosition() const;

    void setScale(const glm::vec3 &scale);

    const glm::vec3 &getScale() const;

private:
    ObjectType type_;
    glm::vec3 scale_, position_;
    glm::mat4 modelMatrix_;
    std::weak_ptr<Scene> scene_ptr_;
    glm::vec4 color_;

private:
    void updateModelMatrix();

};

