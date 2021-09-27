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
class BasicQuadProcess;
class Model;

class Scene {
public:
    glm::vec3 camera_position;
    glm::vec3 looked_position;
    glm::vec3 looked_direction;
    float yaw_angle_ = -150;
    float pitch_angle_ = -20;

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
    std::vector<std::shared_ptr<Box>> box_vec;
    std::shared_ptr<Sphere>light = nullptr;
    std::shared_ptr<Sphere>refract_sphere = nullptr; //表现折射的球
    std::shared_ptr<Sphere> PBR_sphere = nullptr; //表现PBR效果的球

    std::shared_ptr<ShadowProcess> shadow_pass_; // 阴影渲染

    std::shared_ptr<HDRProcess> hdr_pass_; // hd处理

    void RenderPlane(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection);

    void RenderBox(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection);

    void RenderLight(const glm::mat4 &view, const glm::mat4 &projection);

    void RenderReflectSphere(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection);
    void RenderInrradianceSphere(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection);
    void RenderPreflitterSphere(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection);

    void RenderPBRSphere(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection);

private:
    bool b_open_blur_ = true; //是否开启混合效果（按k键）
    void BindPBRTexture(const std::string &texture_name) const;

    void LoadPBRTexture(const std::string &texture_name) const;

    // 模型
private:
    std::shared_ptr<Model> gun_model_;

private:
    std::shared_ptr<Box> sky_box_;
    std::shared_ptr<ColorCubeProcess> sky_process_;
    std::shared_ptr<ColorCubeProcess> irradiance_process_;  //预计算辐照图
    std::shared_ptr<ColorCubeProcess> prefiltter_process_; //重要性采样预处理图
    std::shared_ptr<BasicQuadProcess> brdf_process_; // 预计算brdf部分贴图
    void InitSky(); //  使用HDR资源来初始化天空盒
    void InitIrradiance();  //预先计算辐照图
    void InitPreflitter(); // 重要性采样IBL镜反射预处理
    void InitBRDF(); // 预处理brdf部分
    /**
     * 只支持个顶pbr参数的方式，不支持纹理
     */
    void InitNormalPBRShader() const;
    /**
     * 支持纹理的PBR shader
     */
    void InitPBRTextureShader() const;
    /**
     * 支持pbr model的shader，能够灵活适配不同完整度的model，有的model不给或只给了部分texture,需要pbr参数配合
     */
    void InitPBRModelShader() const;


    void InitShadowpass();

    std::shared_ptr <ColorCubeProcess> GenerateCubepass(float width, float height, bool b_mipmap);

    void RenderSky(const glm::mat4 &view, const glm::mat4 &projection);

    void BRDFRender(const glm::mat4 &view, const glm::mat4 &projection);
};

