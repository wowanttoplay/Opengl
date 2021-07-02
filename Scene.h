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

class Plane;
class Box;
class Sphere;
class ShadowProcess;
class ColorCubeProcess;
class HDRProcess;
class ThreadPool;

class Scene {
public:
    glm::vec3 camera_position;
    glm::vec3 looked_position;
    glm::vec3 looked_direction;
    float yaw_angle_ = -90;
    float pitch_angle_ = 0;

    float scene_width;
    float scene_height;
    float view_angle = 45.0f;

    Scene();
    virtual ~Scene();

    void process_key(int key, int action);

    void SetView(float width, float height);
    void Render();
    void Init();
    void Update(float dt);
private:
    std::shared_ptr<ThreadPool> thread_pool_;

    std::shared_ptr<Plane> plane = nullptr;
    std::shared_ptr<Plane> reflect_plane = nullptr;
    std::vector<std::shared_ptr<Box>> box_vec;
    std::shared_ptr<Sphere>light = nullptr;
    std::shared_ptr<Sphere>refract_sphere = nullptr; //表现折射的球
    std::shared_ptr<Sphere> reflect_sphere = nullptr; //表现反射的球
    std::shared_ptr<Sphere> PBR_sphere = nullptr; //表现PBR效果的球

    std::shared_ptr<ShadowProcess> shadow_pass_; // 阴影渲染

    // TODO：将两个pass改为用两个texture就可以了，不然比较浪费
    std::shared_ptr<ColorCubeProcess> reflect_cube_pass_; // 镜像渲染
    std::shared_ptr<ColorCubeProcess> refract_cube_pass_; // 折射渲染
    std::shared_ptr<HDRProcess> hdr_pass_; // hd处理

    void RenderPlane(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection);
    void RenderRefractPlane(Shader& shader, const glm::mat4& view, const glm::mat4 &projection);

    void RenderBox(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection);

    void RenderLight(const glm::mat4 &view, const glm::mat4 &projection);

    void RenderRefractSphere(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection);

    void RenderReflectSphere(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection);

    void RenderPBRSphere(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection);


private:
    bool b_open_blur_ = true; //是否开启混合效果（按k键）
    void BindPBRTexture(const std::string &texture_name) const;

    void LoadPBRTexture(const std::string &texture_name) const;

private:
    std::shared_ptr<Box> sky_box_;
    std::shared_ptr<ColorCubeProcess> sky_process_;
    void InitSky(); //  使用HDR资源来初始化天空盒

    void InitNormalPBRShader() const;

    void InitPBRTextureShader() const;

    void InitShadowpass();

    std::shared_ptr<ColorCubeProcess> GenerateCubepass();

    void InitNormalLightShader() const;

    void RenderSky(const glm::mat4 &view, const glm::mat4 &projection);
};

