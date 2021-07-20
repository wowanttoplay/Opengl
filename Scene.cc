//
// Created by virgil on 2021/6/10.
//

#include "Scene.h"
#include "ResourceManager.h"
#include "RenderObject/Plane.h"
#include "RenderObject/Box.h"
#include "RenderObject/Sphere.h"

#include "Thread/ThreadPool.h"
#include "Thread/Task.h"
#include "Log/LogUtil.h"
#include "Tool/PrintTool.h"
#include "RenderPass/ShadowProcess.h"
#include "RenderPass/ColorCubeProcess.h"
#include "RenderPass/HDRProcess.h"
#include "RenderPass/BasicQuadProcess.h"
#include "Model/Model.h"
#include <mutex>
#include <thread>

using namespace std;

once_flag sky_init;
const uint32_t box_num = 2;
const std::string kFloorName = "floor";
const std::string kMetalname = "metal";
const std::string kShingles1 = "shingles1";
const std::string kRockyShoreLine = "rocky-shoreline1";
const std::string kAngledTiledFloor = "angled-tiled-floor";
const std::string kSkyBoxHdr = "sky_hdr";
const std::string kGranite = "gray-granite-flecks";
const std::string kShinyMetal = "worn-shiny-metal";

const std::string kPBR = "pbr";
const std::string kPBRTexture = "PBR_texture";
const std::string kPbrModel = "PBR_Model";
const std::string kBoxName = "Wall";
const std::string kLight = "Sphere";
const std::string kReflectShader = "reflect_sphere";
const std::string kGlassTextureName = "glass";
const std::string kTextureLightShaderName = "texture_light"; //考虑了纹理与光照的shader
const std::string kShadowShaderName = "shadow";
const std::string kShadowTextureLightShaderName = "shadow_texture_light"; // 考虑了阴影、 纹理、光照的shader
const std::string kSkyBoxGenerateShader = "sky_generate";
const std::string kIrradianceGenerateShader = "irradiance_generate";
const std::string kPrefiltterShader = "prefiltter";
const std::string kBrdf = "brdf";
const std::string kSkyBoxRender = "sky_render";
const std::string kTextureShaderName = "texture";

// projection
const float near_plane = 0.1f, far_plane = 100.f;
//box
glm::vec3 box_position = glm::vec3(0.0f, 0.0f, 0.0f);
// refract sphere
glm::vec3 refract_sphere_position = glm::vec3(0.0f, 1.0f, 5.0f);
// reflect sphere
glm::vec3 reflect_sphere_position = glm::vec3(2.0f, 3.0f, -2.0f);
glm::vec3 inrradiance_sphere_position = glm::vec3(4.0, 3.0, -2.0);
glm::vec3 preflitter_sphere_position = glm::vec3(6.0, 3.0, -2.0);
// PBR sphere
glm::vec3 PBR_position = glm::vec3(3.0f, 1.0f, -2.0f);
// light
const glm::vec3 light_center = glm::vec3(0.0f, 7.0f, 0.0f);;
glm::vec3 light_position = light_center;
const glm::vec3 light_base_color = glm::vec3(300.0f, 300.0f, 300.0f);
glm::vec3 light_color = light_base_color;
float light_constant = 1.0f, light_linear = 0.22f, light_quadratic = 0.20f;
const float light_move_radius = 5.0f;
//shadow
const float kShadowFarPlane = 100.0f;

Scene::Scene() {
    thread_pool_ = make_shared<ThreadPool>(3, "scene_pool");
}


Scene::~Scene() {
}


void Scene::Init() {
    camera_position = glm::vec3(8.96f, 3.8f, 0.03f);
    looked_direction.x = cos(glm::radians(pitch_angle_)) * cos(glm::radians(yaw_angle_));
    looked_direction.y = sin(glm::radians(pitch_angle_));
    looked_direction.z = cos(glm::radians(pitch_angle_)) * sin(glm::radians(yaw_angle_));
//    looked_direction = glm::vec3(0, 0, -3);
    looked_position = camera_position + looked_direction;

    // init png resource

    LoadPBRTexture(kMetalname);
    LoadPBRTexture(kGranite);
    LoadPBRTexture(kShinyMetal);
//    LoadPBRTexture(kAngledTiledFloor);
//    LoadPBRTexture(kFloorName);
    ResourceManager::LoadTexture("../Data/Png/Topanga_Forest_B_3k.hdr", kSkyBoxHdr);
    ResourceManager::LoadShader("../Data/sky.vs", "../Data/sky.fs", nullptr, kSkyBoxGenerateShader);
    ResourceManager::LoadShader("../Data/sky.vs", "../Data/irradiance.fs", nullptr, kIrradianceGenerateShader);
    ResourceManager::LoadShader("../Data/sky.vs", "../Data/preflitter.fs", nullptr, kPrefiltterShader);
    ResourceManager::LoadShader("../Data/brdf.vs", "../Data/brdf.fs", nullptr, kBrdf);
    // init light resource
    ResourceManager::LoadShader("../Data/Sphere.vs", "../Data/Sphere.fs", nullptr, kLight);
    // init shadow resource
    ResourceManager::LoadShader("../Data/shadow_cube_map.vs", "../Data/shadow_cube_map.fs",
                                nullptr,
                                kShadowShaderName);
    ResourceManager::LoadShader("../Data/sky_box.vs", "../Data/sky_box.fs", nullptr, kSkyBoxRender);
    ResourceManager::LoadShader("../Data/Sphere.vs", "../Data/sphere_reflect.fs", nullptr, kReflectShader);
    ResourceManager::LoadShader("../Data/texture.vs", "../Data/texture.fs", nullptr, kTextureShaderName);
    // init shadow render
    InitNormalLightShader();

    // init PBR shader
    InitNormalPBRShader();

    // init PBR with texture shader
    InitPBRTextureShader();
    // init PBR width model shader
    InitPBRModelShader();

    this->plane = std::make_shared<Plane>();
    this->reflect_plane = std::make_shared<Plane>();
    for (int i = 0; i < box_num; ++i) {
        box_vec.emplace_back(make_shared<Box>());
    }
    sky_box_ = std::make_shared<Box>();
    light = make_shared<Sphere>(20, 20);
    refract_sphere = make_shared<Sphere>(30, 30);
    reflect_sphere = make_shared<Sphere>(30, 30);
    PBR_sphere = make_shared<Sphere>(30, 30);
//    this->house_model_ = make_shared<Model>("../Data/model/spot/uploads_files_2667772_Spot.glb");
//    this->house_model_ = make_shared<Model>("../Data/model/rocket/uploads_files_2652037_TheRocket.glb");
    this->house_model_ = make_shared<Model>("../Data/model/cerberus/Cerberus_LP.FBX");

    // 渲染pass
    InitShadowpass();

    this->reflect_cube_pass_ = GenerateCubepass(1024, 1024, false);
    this->refract_cube_pass_ = GenerateCubepass(1024, 1024, false);
    this->sky_process_ = GenerateCubepass(1024, 1024, true);
    this->irradiance_process_ = GenerateCubepass(32, 32, false);
    this->prefiltter_process_ = GenerateCubepass(512, 512, true);
    this->brdf_process_ = make_shared<BasicQuadProcess>(512, 512);

    this->hdr_pass_ = make_shared<HDRProcess>(this->scene_width, this->scene_height);
    InitSky();
    InitIrradiance();
    InitPreflitter();
    InitBRDF();
}

void Scene::InitNormalLightShader() const {
    Shader shadow_texture_light = ResourceManager::LoadShader("../Data/shadow_texture_light.vs",
                                                              "../Data/shadow_texture_light.fs", nullptr,
                                                              kShadowTextureLightShaderName);

    shadow_texture_light.Use();
    shadow_texture_light.SetInteger("texture0", 0);
    shadow_texture_light.SetInteger("depth_texture", 1);
    shadow_texture_light.SetInteger("reflect_cube_map", 2);
    shadow_texture_light.SetInteger("refract_cube_map", 3);
    shadow_texture_light.SetFloat("far_plane", kShadowFarPlane);
    shadow_texture_light.SetInteger("b_reflected", false);
    shadow_texture_light.SetInteger("b_refracted", false);
    shadow_texture_light.SetFloat("material.ambient_ratio", 0.05);
    shadow_texture_light.SetFloat("material.diffuse_ratio", 1.0);
    shadow_texture_light.SetFloat("material.specular_ratio", 32.0);
}

shared_ptr<ColorCubeProcess> Scene::GenerateCubepass(float width, float height, bool b_mipmap) {
    shared_ptr<ColorCubeProcess> rst = make_shared<ColorCubeProcess>(width, height, b_mipmap);
    rst->SetNearAndFar(0.1f, 100.f);
    return rst;
}

void Scene::InitShadowpass() {
    shadow_pass_ = make_shared<ShadowProcess>();
    shadow_pass_->SetNearAndFar(0.1f, kShadowFarPlane);
}

void Scene::InitPBRTextureShader() const {
    Shader PBR_texture_shader = ResourceManager::LoadShader("../Data/PBR.vs", "../Data/PBR_texture.fs", nullptr,
                                                            kPBRTexture);
    PBR_texture_shader.Use();
    PBR_texture_shader.SetInteger("albedoMap", 0);
    PBR_texture_shader.SetInteger("normalMap", 1);
    PBR_texture_shader.SetInteger("metallicMap", 2);
    PBR_texture_shader.SetInteger("roughnessMap", 3);
    PBR_texture_shader.SetInteger("aoMap", 4);
//    PBR_texture_shader.SetInteger("heightMap", 5);
    PBR_texture_shader.SetInteger("depthMap", 6);
    PBR_texture_shader.SetInteger("irradianceMap", 7);
    PBR_texture_shader.SetInteger("prefilterMap", 8);
    PBR_texture_shader.SetInteger("brdfLUT", 9);
    PBR_texture_shader.SetFloat("farPlane", kShadowFarPlane);
}

void Scene::InitNormalPBRShader() const {
    Shader PBR_shader = ResourceManager::LoadShader("../Data/PBR.vs", "../Data/PBR.fs", nullptr, kPBR);
    PBR_shader.Use();
    PBR_shader.SetInteger("albedoTexture", 0);
    PBR_shader.SetInteger("depthMap", 1);
    PBR_shader.SetFloat("farPlane", kShadowFarPlane);

    PBR_shader.SetFloat("ao", 1.0);
    PBR_shader.SetFloat("roughness", 0.1);
    PBR_shader.SetFloat("metallic", 0.6);
}

void Scene::LoadPBRTexture(const string &texture_name) const {
    vector<string> str_vec{"albedo", "ao", "height", "metallic", "normal", "roughness"};
    for (int i = 0; i < str_vec.size(); ++i) {
        string str = str_vec.at(i);
        ResourceManager::LoadTexture("../Data/Png/" + texture_name + "_" + str + ".png", texture_name + "_" + str);
    }
}

void Scene::Render() {
    // 为了统一所有的渲染，cube的绘制不再使用gs，而是绘制6次来完成,否则随着效果与元素的增加，都得加一个gs，不方便写
    // 准备阴影贴图
    this->shadow_pass_->Render([=](glm::mat4 view, glm::mat4 projection) -> void {
        Shader shadow_map_shader = ResourceManager::GetShader(kShadowShaderName);
        shadow_map_shader.SetVector3f("light_position", light_position);
        shadow_map_shader.SetFloat("far_plane", kShadowFarPlane);
        this->RenderPBRSphere(shadow_map_shader, view, projection);
        this->house_model_->Render(shadow_map_shader, glm::mat4(), glm::mat4());
    });

    //正常渲染
    this->hdr_pass_->PreRender([=]() -> void {
        glViewport(0, 0, scene_width, scene_height);
        glClearColor(0.1, 0.1, 0.1, 0.1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::lookAt(camera_position, looked_position, glm::vec3(0, 1, 0));
        glm::mat4 projection = glm::perspective(view_angle, scene_width / scene_height, 0.1f, 100.0f);

        Shader PBR_texture_shader = ResourceManager::GetShader(kPBRTexture);
        PBR_texture_shader.Use();

        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->shadow_pass_->depth_cube_map_);
        glActiveTexture(GL_TEXTURE7);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->irradiance_process_->color_cube_map_);
        glActiveTexture(GL_TEXTURE8);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->prefiltter_process_->color_cube_map_);
        glActiveTexture(GL_TEXTURE9);
        this->brdf_process_->texture_.Bind();
        RenderPBRSphere(PBR_texture_shader, view, projection);



        Shader model_shader = ResourceManager::GetShader(kPbrModel);
        model_shader.Use();
        this->house_model_->Render(model_shader, view, projection);

//        Shader reflect_shader = ResourceManager::GetShader(kReflectShader);
//        RenderReflectSphere(reflect_shader, view, projection);
//        RenderInrradianceSphere(reflect_shader, view, projection);
//        RenderPreflitterSphere(reflect_shader, view, projection);
        // sky
        RenderSky(view, projection);

        // render brdf
//        BRDFRender(view, projection);

    });

    if (b_open_blur_) {
        this->hdr_pass_->BrightColorRender();
        this->hdr_pass_->BlurProcess();
        this->hdr_pass_->FloodLightRender();
    } else {
        this->hdr_pass_->HDRRender();
    }
}

void Scene::BRDFRender(const glm::mat4 &view, const glm::mat4 &projection) {
    Shader texture_shader = ResourceManager::GetShader(kTextureShaderName);
    texture_shader.Use();
    glActiveTexture(GL_TEXTURE0);
    texture_shader.SetInteger("texture0", 0);
    texture_shader.SetMatrix4("model", glm::mat4(2.0));
    texture_shader.SetMatrix4("view", view);
    texture_shader.SetMatrix4("projection", projection);
    brdf_process_->texture_.Bind();
    plane->Render(texture_shader);
}


void Scene::RenderReflectSphere(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection) {
    shader.Use();
    shader.SetMatrix4("view", view);
    shader.SetMatrix4("projection", projection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->sky_process_->color_cube_map_);
    glm::mat4 refract_sphere_model = glm::mat4(1.0f);
    refract_sphere_model = glm::translate(refract_sphere_model, reflect_sphere_position);
    shader.SetMatrix4("Model", refract_sphere_model);
    refract_sphere->Render(shader);
}

void Scene::RenderInrradianceSphere(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection) {
    shader.Use();
    shader.SetMatrix4("view", view);
    shader.SetMatrix4("projection", projection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->irradiance_process_->color_cube_map_);
    glm::mat4 refract_sphere_model = glm::mat4(1.0f);
    refract_sphere_model = glm::translate(refract_sphere_model, inrradiance_sphere_position);
    shader.SetMatrix4("Model", refract_sphere_model);
    refract_sphere->Render(shader);
}


void Scene::RenderRefractSphere(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection) {
    shader.SetMatrix4("view", view);
    shader.SetMatrix4("projection", projection);
    glActiveTexture(GL_TEXTURE0);
    ResourceManager::GetTexture(kGlassTextureName)->Bind();
    glm::mat4 refract_sphere_model = glm::mat4(1.0f);
    refract_sphere_model = glm::translate(refract_sphere_model, refract_sphere_position);
    shader.SetMatrix4("Model", refract_sphere_model);
    refract_sphere->Render(shader);
}

void Scene::RenderLight(const glm::mat4 &view, const glm::mat4 &projection) {
    Shader light_shader = ResourceManager::GetShader(kLight);
    light_shader.Use();
    glm::mat4 light_model = glm::mat4(1.0);
    light_model = glm::translate(light_model, light_position);
    light_model = glm::scale(light_model, glm::vec3(0.5f));
    light_shader.SetMatrix4("Model", light_model);
    light_shader.SetMatrix4("view", view);
    light_shader.SetMatrix4("projection", projection);
    light->Render(light_shader);
}

void Scene::RenderBox(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection) {// box
    shader.Use();
    shader.SetMatrix4("projection", projection);
    shader.SetMatrix4("view", view);
    BindPBRTexture(kAngledTiledFloor);

    for (int i = 0; i < box_num; ++i) {
        glm::mat4 box_model = glm::mat4(1.0f);
        box_model = glm::translate(box_model, box_position + glm::vec3(i * 1.1, 0, -i * 1.3));
        box_model = glm::scale(box_model, glm::vec3(1.0f, 1.5f, 1.0f));
        shader.SetMatrix4("Model", box_model);
        box_vec.at(i)->Render(shader);
    }
}

void Scene::RenderPlane(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection) {//plane
    shader.Use();
    shader.SetMatrix4("projection", projection);
    shader.SetMatrix4("view", view);
    BindPBRTexture(kFloorName);

    glm::mat4 plane_model = glm::mat4(1.0f);
    shader.SetMatrix4("Model", plane_model);
    plane->Render(shader);
}

void Scene::BindPBRTexture(const string &texture_name) const {
    glActiveTexture(GL_TEXTURE0);
    if (ResourceManager::GetTexture(texture_name + "_albedo")) {
        ResourceManager::GetTexture(texture_name + "_albedo")->Bind();
    }
    glActiveTexture(GL_TEXTURE1);
    if (ResourceManager::GetTexture(texture_name + "_normal")) {
        ResourceManager::GetTexture(texture_name + "_normal")->Bind();
    }
    glActiveTexture(GL_TEXTURE2);
    if (ResourceManager::GetTexture(texture_name + "_metallic")) {
        ResourceManager::GetTexture(texture_name + "_metallic")->Bind();
    }
    glActiveTexture(GL_TEXTURE3);
    if (ResourceManager::GetTexture(texture_name + "_roughness")) {
        ResourceManager::GetTexture(texture_name + "_roughness")->Bind();
    }
    glActiveTexture(GL_TEXTURE4);
    if (ResourceManager::GetTexture(texture_name + "_ao")) {
        ResourceManager::GetTexture(texture_name + "_ao")->Bind();
    }
//    glActiveTexture(GL_TEXTURE5);
//    if (ResourceManager::GetTexture(texture_name + "_height")) {
//        ResourceManager::GetTexture(texture_name + "_height")->Bind();
//    }
}

void Scene::RenderRefractPlane(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection) {
    shader.Use();
    shader.SetMatrix4("projection", projection);
    shader.SetMatrix4("view", view);
    glActiveTexture(GL_TEXTURE0);
    ResourceManager::GetTexture(kGlassTextureName)->Bind();
    glm::mat4 plane_model = glm::mat4(1.0f);
    plane_model = glm::translate(plane_model, refract_sphere_position);
    plane_model = glm::rotate(plane_model, glm::radians(90.f), glm::vec3(1.0, 0.0, 0.0));
    plane_model = glm::scale(plane_model, glm::vec3(0.06, 0.06, 0.06));
    shader.SetMatrix4("Model", plane_model);
    plane->Render(shader);
}

void Scene::RenderPBRSphere(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection) {
    shader.Use();
    vector<string> spheres{kMetalname, kGranite, kShinyMetal};
    for (int i = 0; i < 3; ++i) {
        BindPBRTexture(spheres.at(i));
        shader.SetMatrix4("projection", projection);
        shader.SetMatrix4("view", view);
        glm::mat4 sphere_model = glm::mat4(1.0f);
        sphere_model = glm::translate(sphere_model, PBR_position + glm::vec3(2.5 * i, 0.0, 0.0));
        shader.SetMatrix4("model", sphere_model);
        PBR_sphere->Render(shader);
    }
}

void Scene::SetView(float width, float height) {
    this->scene_width = width;
    this->scene_height = height;
    logE("scene width: %f, height :%f", width, height);
}

void Scene::Update(float dt) {
    // 更新相机
    looked_direction.x = cos(glm::radians(pitch_angle_)) * cos(glm::radians(yaw_angle_));
    looked_direction.y = sin(glm::radians(pitch_angle_));
    looked_direction.z = cos(glm::radians(pitch_angle_)) * sin(glm::radians(yaw_angle_));
    looked_position = camera_position + looked_direction;
    // 更新light的相关属性
    light_position = light_center + glm::vec3(sin(dt / 3) * light_move_radius, 0, cos(dt / 3) * light_move_radius);
//    light_color = light_base_color + glm::vec3(0, -sin(dt)*0.8, -cos(dt)*0.8);
    Shader light_shader = ResourceManager::GetShader(kLight);
    light_shader.Use();
    light_shader.SetVector3f("color", light_color);

    // 更新渲染的相关属性
    plane->Update(dt);
    // 更新render pass中光源的位置，实时更改shadow map
    this->shadow_pass_->SetLightPosition(light_position);
    // 设置阴影、纹理、光照的着色器
    Shader shadow_texture_light = ResourceManager::GetShader(kShadowTextureLightShaderName);
    shadow_texture_light.Use();
    shadow_texture_light.SetVector3f("light.position", light_position);
    shadow_texture_light.SetVector3f("light.color", light_color);
    shadow_texture_light.SetFloat("light.constant", light_constant);
    shadow_texture_light.SetFloat("light.linear", light_linear);
    shadow_texture_light.SetFloat("light.quadratic", light_quadratic);
    shadow_texture_light.SetVector3f("cameraPosition", camera_position);
    // 设置PBR着色器
    Shader PBR_shader = ResourceManager::GetShader(kPBR);
    PBR_shader.Use();
    PBR_shader.SetVector3f("light_color", light_color);
    PBR_shader.SetVector3f("lightPosition", light_position);
    PBR_shader.SetVector3f("cameraPosition", camera_position);
    // 设置PBR texture着色器
    Shader PBR_texture_shader = ResourceManager::GetShader(kPBRTexture);
    PBR_texture_shader.Use();
    PBR_texture_shader.SetVector3f("cameraPosition", camera_position);
    PBR_texture_shader.SetVector3f("lightPosition", light_position);
    PBR_texture_shader.SetVector3f("light_color", light_color);

    Shader pbr_model_shader = ResourceManager::GetShader(kPbrModel);
    pbr_model_shader.Use();
    pbr_model_shader.SetVector3f("cameraPosition", camera_position);
    pbr_model_shader.SetVector3f("lightPosition", light_position);
    pbr_model_shader.SetVector3f("light_color", light_color);
}

void Scene::process_key(int key, int action) {
    logE("scene, press key : %d", key);
    if (key == GLFW_KEY_W) {
        camera_position += looked_direction;
    } else if (key == GLFW_KEY_S) {
        camera_position -= looked_direction;
    } else if (key == GLFW_KEY_A) {
        camera_position -= glm::normalize(glm::cross(looked_direction, glm::vec3(0, 1, 0)));
    } else if (key == GLFW_KEY_D) {
        camera_position += glm::normalize(glm::cross(looked_direction, glm::vec3(0, 1, 0)));
    } else if (key == GLFW_KEY_Q) {
        yaw_angle_ -= 10;
    } else if (key == GLFW_KEY_E) {
        yaw_angle_ += 10;
    } else if (key == GLFW_KEY_Z) {
        camera_position += glm::vec3(0, 1, 0);
    } else if (key == GLFW_KEY_X) {
        camera_position += glm::vec3(0, -1, 0);
    } else if (key == GLFW_KEY_C) {
        pitch_angle_ += 10;
    } else if (key == GLFW_KEY_V) {
        pitch_angle_ -= 10;
    } else if (key == GLFW_KEY_O && action == GLFW_PRESS) {
        this->hdr_pass_->SetExposure(this->hdr_pass_->GetExposure() - 0.1);
    } else if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        this->hdr_pass_->SetExposure(this->hdr_pass_->GetExposure() + 0.1);
    } else if (key == GLFW_KEY_K && action == GLFW_PRESS) {
        this->b_open_blur_ = !this->b_open_blur_;
    }

    logE("printf camara info");
    logE("camera info : yaw:%f, pitch:%f", yaw_angle_, pitch_angle_);
    tool::Print(camera_position);
//    tool::Print(camera_position);
//    tool::Print(looked_direction);
}

void Scene::InitSky() {
    logI("init sky cube map");
    Shader shader = ResourceManager::GetShader(kSkyBoxGenerateShader);
    shader.Use();
    shader.SetInteger("HDRMap", 0);
    glActiveTexture(GL_TEXTURE0);
    ResourceManager::GetTexture(kSkyBoxHdr)->Bind();
    this->sky_process_->SetCenter(glm::vec3(0, 0, 0));
    this->sky_process_->Render([=](glm::mat4 view, glm::mat4 projection) -> void {
        Shader shader = ResourceManager::GetShader(kSkyBoxGenerateShader);
        shader.Use();
        shader.SetMatrix4("view", view);
        shader.SetMatrix4("projection", projection);
        sky_box_->Render(shader);
    }, 0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->sky_process_->color_cube_map_);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
}

void Scene::RenderSky(const glm::mat4 &view, const glm::mat4 &projection) {
    Shader sky_shader = ResourceManager::GetShader(kSkyBoxRender);
    sky_shader.Use();
    sky_shader.SetInteger("skyMap", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->sky_process_->color_cube_map_);
    sky_shader.SetMatrix4("view", view);
    sky_shader.SetMatrix4("projection", projection);
    glDepthFunc(GL_LEQUAL);
    sky_box_->Render(sky_shader);
    glDepthFunc(GL_LESS);
}

void Scene::InitIrradiance() {
    logI("init irradiance map");
    Shader shader = ResourceManager::GetShader(kIrradianceGenerateShader);
    shader.Use();
    shader.SetInteger("curbMap0", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->sky_process_->color_cube_map_);
    this->irradiance_process_->SetCenter(glm::vec3(0, 0, 0));
    this->irradiance_process_->Render([=](glm::mat4 view, glm::mat4 projection) -> void {
        Shader shader = ResourceManager::GetShader(kIrradianceGenerateShader);
        shader.Use();
        shader.SetMatrix4("view", view);
        shader.SetMatrix4("projection", projection);
        sky_box_->Render(shader);
    }, 0);
}

void Scene::InitPreflitter() {
    logI("init preflitter map");
    Shader shader = ResourceManager::GetShader(kPrefiltterShader);
    shader.Use();
    shader.SetInteger("cubeMap0", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->sky_process_->color_cube_map_);
    this->prefiltter_process_->SetCenter(glm::vec3(0, 0, 0));
    auto func = [=](glm::mat4 view, glm::mat4 projection) -> void {
        Shader shader = ResourceManager::GetShader(kPrefiltterShader);
        shader.Use();
        shader.SetMatrix4("view", view);
        shader.SetMatrix4("projection", projection);
        sky_box_->Render(shader);
    };
    // 生成5级渐远纹理
    const int kMaxMipLevels = 5;
    for (int i = 0; i < kMaxMipLevels; ++i) {
        float roughness = float(i) / (float) (kMaxMipLevels - 1);
        shader.SetFloat("roughness", roughness);
        this->prefiltter_process_->Render(func, i);
    }
}

void Scene::RenderPreflitterSphere(Shader &shader, const glm::mat4 &view, const glm::mat4 &projection) {
    shader.Use();
    shader.SetMatrix4("view", view);
    shader.SetMatrix4("projection", projection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->prefiltter_process_->color_cube_map_);
    glm::mat4 preflitter_sphere_model = glm::mat4(1.0f);
    preflitter_sphere_model = glm::translate(preflitter_sphere_model, preflitter_sphere_position);
    shader.SetMatrix4("Model", preflitter_sphere_model);
    refract_sphere->Render(shader);
}

void Scene::InitBRDF() {
    Shader shader = ResourceManager::GetShader(kBrdf);
    shader.Use();
    this->brdf_process_->Render([=]() -> void {
        this->plane->Render(shader);
    });
}

void Scene::InitPBRModelShader() const {
    Shader PBR_model_shader = ResourceManager::LoadShader("../Data/PBR.vs", "../Data/PBR_Model.fs", nullptr,
                                                          kPbrModel);
    PBR_model_shader.Use();
    PBR_model_shader.SetInteger("albedoMap", 0);
    PBR_model_shader.SetInteger("normalMap", 1);
    PBR_model_shader.SetInteger("metallicMap", 2);
    PBR_model_shader.SetInteger("roughnessMap", 3);
    PBR_model_shader.SetInteger("aoMap", 4);
    PBR_model_shader.SetInteger("depthMap", 6);
    PBR_model_shader.SetInteger("irradianceMap", 7);
    PBR_model_shader.SetInteger("prefilterMap", 8);
    PBR_model_shader.SetInteger("brdfLUT", 9);
    PBR_model_shader.SetFloat("farPlane", kShadowFarPlane);
}








