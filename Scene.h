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

class DebugPlane;
class Scene : public std::enable_shared_from_this<Scene>{
public:
    Scene(uint32_t width, uint32_t height, const std::string& resource_dir);
    virtual ~Scene();
    void draw();
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
    void setCamera(const std::shared_ptr<Camera> &camera);

    /**
     * 获取资源管理器
     * @return resource manager 的智能指针
     */
    std::shared_ptr<ResourceManager> getResourceManager();

    const std::shared_ptr<BaseLight> &getLight() const;
    void setLight(const std::shared_ptr<BaseLight> &light);

    const std::shared_ptr<Texture2D> &getShadowMap() const;

    /**
     * 是否开启阴影
     * @param open_shadow
     */
    void setOpenShadow(bool open_shadow);

    void setDebugShadow(bool debug_shadow);

public:
    // 外部回调
    void processKey(int key, int action);
    void mouseCallBack(double x, double y);
    void mouseScrollCallBack(double x_offset, double y_offset);

private:
    std::shared_ptr<Camera> camera_ = nullptr;
    std::shared_ptr<ResourceManager> resource_manager_ = nullptr;
    uint32_t width_ = 0, height_ = 0; // viewport 大小
    std::vector<std::shared_ptr<BaseObject>> objects_; // 所有可绘制物体
    std::shared_ptr<BaseLight> light_;
    GLuint FBO_; // 常用的FBO，用于离屏渲染
/////////////////////绘制阴影相关
    bool open_shadow_ = false;
public:
    bool isOpenShadow() const;

private:
    bool debug_shadow_ = false;
    std::shared_ptr<Texture2D>shadow_map_ = nullptr;


public:
    void setOpenAo(bool openAo);

    void setDebugAo(bool debugAo);

    bool isOpenAo() const;

private:
    bool open_ao_ = false;
    bool debug_ao_ = false;
    std::shared_ptr<Texture2D>ao_map_ = nullptr;
private:
    void drawShaow();
    void drawAoMap();
    void debugAoMap();
    void normalDraw();


private:
    void debug();
    void debugShadowMap();
    std::shared_ptr<DebugPlane> debug_plane_ = nullptr;
};

