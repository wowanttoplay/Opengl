//
// Created by virgil on 2021/6/10.
//

#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <vector>
#include "Shader.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "RenderObject/BaseObject.h"
#include "RenderObject/Light/BaseLight.h"

class Scene : public std::enable_shared_from_this<Scene>{
public:
    Scene(uint32_t width, uint32_t height, const std::string& resource_dir);
    virtual ~Scene();
    void Draw();
    void Update();

    /**
     * 推入新的可绘制物体
     * @param object
     */
    void pushObject(std::shared_ptr<BaseObject> object);

    /**
     * 获取相机的智能指针
     * @return camera的智能指针
     */
    std::shared_ptr<Camera> getCamera();

    /**
     * 获取资源管理器
     * @return resource manager 的智能指针
     */
    std::shared_ptr<ResourceManager> getResourceManager();
public:
    // 外部回调
    void ProcessKey(int key, int action);
    void MouseCallBack(double x, double y);
    void MouseScrollCallBack(double x_offset, double y_offset);
private:
    std::shared_ptr<Camera> camera_ = nullptr;
public:
    void setCamera(const std::shared_ptr<Camera> &camera);

private:
    std::shared_ptr<ResourceManager> resource_manager_ = nullptr;
    uint32_t width_ = 0, height_ = 0; // viewport 大小
    std::vector<std::shared_ptr<BaseObject>> objects_; // 所有可绘制物体
    std::shared_ptr<BaseLight> light_;
public:
    const std::shared_ptr<BaseLight> &getLight() const;

public:
    void setLight(const std::shared_ptr<BaseLight> &light);
};

