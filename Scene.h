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
    std::shared_ptr<Texture2D>ao_depth_map_ = nullptr; // 记录深度值
    std::shared_ptr<Texture2D>ao_position_map_ = nullptr; // 记录世界空间的位置信息
    std::shared_ptr<Texture2D>ao_normal_map_ = nullptr; // 记录世界空间的法线信息
    std::shared_ptr<Texture2D>ao_albedoColor_map_ = nullptr; // 记录基础颜色信息
private:
    void drawShaow(); // 准备光源的深度图
    void drawGBufferMap(); // 准备g buffer的纹理，为了ao方便，所有的数据都是在观察空间的，小心搞错
    void debugAOBufferMap(); // debug 显示g buffer的纹理
    void forwardDraw(); //前向渲染
    void drawAo(); // 延迟渲染

private:
    void debug();
    void debugShadowMap();
    std::shared_ptr<DebugPlane> debug_plane_ = nullptr;
    std::vector<std::function<void()>> debug_fucntions_;
};

