//
// Created by virgil on 2021/6/10.
//

#include <random>
#include "Scene.h"
#include "ResourceManager.h"
#include "RenderObject/Box.h"
#include "glm/gtx/string_cast.hpp"
#include "glog/logging.h"
#include "RenderObject/Debug/DebugPlane.h"

using namespace std;
using namespace google;


Scene::~Scene() {
    LOG_AT_LEVEL(ERROR) << "~Scene(), ptr : " << this;
    glDeleteFramebuffers(1, &FBO_);
}

void Scene::draw() {
    // 检测是否绘制阴影
    if (open_shadow_) drawShaow();
    if (open_ao_) {
        prepareAOGBuffer();
        prepareAOMap();
        blurAoMap();
        forwardDraw();
    } else {
        forwardDraw();
    }
    debug();
}

void Scene::forwardDraw() {
    glViewport(0, 0, width_, height_);
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (const auto &object: objects_) {
        object->draw();
    }
    light_->draw();
}

void Scene::drawShaow() {
    glViewport(0, 0, width_, height_);
    light_->setAspect(width_ / height_);
    if (!glIsFramebuffer(FBO_)) {
        LOG(WARNING) << "generate FBO";
        glGenFramebuffers(1, &FBO_);
    }
    if (!shadow_map_) {
        shadow_map_ = make_shared<Texture2D>(GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_CLAMP_TO_BORDER,
                                             GL_CLAMP_TO_BORDER, GL_NEAREST,
                                             GL_NEAREST, GL_FLOAT);
        shadow_map_->generate(width_, height_, NULL);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, FBO_);
    shadow_map_->bind(0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadow_map_->getId(), 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    glBindFramebuffer(GL_FRAMEBUFFER, FBO_);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOG(ERROR) << "frame buffer is not complete";
    }
    glClear(GL_DEPTH_BUFFER_BIT);

    for (const auto &object: objects_) {
        object->drawDepthMap(light_->getViewMatrix(), light_->getProjectionMatrix());
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Scene::Update() {

}

Scene::Scene(uint32_t width, uint32_t height, const string &resource_dir) : width_(width), height_(height) {
    LOG_AT_LEVEL(ERROR) << "Scene()" << ", ptr : " << this << "\t width : " << width_ << "\t height : " << height_;
    resource_manager_ = make_shared<ResourceManager>(resource_dir);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    CHECK(resource_manager_ != nullptr);
}

void Scene::processKey(int key, int action) {
    const float kDeltatime = 0.1f;
    if (key == GLFW_KEY_W)
        camera_->ProcessKeyboard(Camera_Movement::FORWARD, kDeltatime);
    if (key == GLFW_KEY_S)
        camera_->ProcessKeyboard(Camera_Movement::BACKWARD, kDeltatime);
    if (key == GLFW_KEY_A)
        camera_->ProcessKeyboard(Camera_Movement::LEFT, kDeltatime);
    if (key == GLFW_KEY_D)
        camera_->ProcessKeyboard(Camera_Movement::RIGHT, kDeltatime);
}

void Scene::mouseCallBack(double x, double y) {
    // 为了避免剧烈抖动，需要在鼠标第一次返回位置时，确立鼠标的初始位置，不做移动
    static bool first = true;
    static double x_pos_last = 0.0, y_pos_last = 0.0;

    if (first) {
        x_pos_last = x;
        y_pos_last = y;
        first = false;
    }
    double x_offset = x - x_pos_last;
    double y_offset = y - y_pos_last;
    x_pos_last = x;
    y_pos_last = y;
    camera_->ProcessMouseMovement(x_offset, y_offset);
}

void Scene::mouseScrollCallBack(double x_offset, double y_offset) {
    camera_->ProcessMouseScroll(y_offset);
}

std::shared_ptr<Camera> Scene::getCamera() {
    return camera_;
}

std::shared_ptr<ResourceManager> Scene::getResourceManager() {
    return resource_manager_;
}

void Scene::pushObject(std::shared_ptr<BaseObject> object) {
    if (!object) {
        LOG(ERROR) << "Push object is nullptr";
        return;
    }

    LOG(WARNING) << "push object in scene, object : " << object;
    objects_.push_back(object);
    LOG(WARNING) << "current objects size : " << objects_.size();
}

void Scene::setLight(const shared_ptr<BaseLight> &light) {
    light_ = light;
}

const shared_ptr<BaseLight> &Scene::getLight() const {
    return light_;
}

void Scene::setCamera(const shared_ptr<Camera> &camera) {
    camera_ = camera;
}

void Scene::setOpenShadow(bool open_shadow) {
    open_shadow_ = open_shadow;
}

const shared_ptr<Texture2D> &Scene::getShadowMap() const {
    return shadow_map_;
}

void Scene::setDebugShadow(bool debug_shadow) {
    debug_shadow_ = debug_shadow;
}

void Scene::debug() {
    debug_fucntions_.clear();
    // 是否绘制阴影debug图
    if (open_shadow_ && debug_shadow_) {
        debugShadowMap();
    }
    if (open_ao_ && debug_ao_) {
        debugAOBufferMap();
    }
    float num = float(debug_fucntions_.size());
    for (int i = 0; i < debug_fucntions_.size(); ++i) {
        auto func = debug_fucntions_.at(i);
        glViewport(width_ * i / debug_fucntions_.size(), height_ * (1 - 1.0 / num), float(width_) / num,
                   float(height_) / num);
        debug_fucntions_.at(i)();
    }
}

void Scene::debugShadowMap() {
    if (!debug_plane_) {
        debug_plane_ = make_shared<DebugPlane>(shared_from_this());
    }
    debug_fucntions_.push_back([=]() {
        debug_plane_->drawTexture(shadow_map_, DebugType::DebugType_Shadow);
    });
}

bool Scene::isOpenShadow() const {
    return open_shadow_;
}

bool Scene::isOpenAo() const {
    return open_ao_;
}

void Scene::setOpenAo(bool openAo) {
    open_ao_ = openAo;
}

void Scene::setDebugAo(bool debugAo) {
    debug_ao_ = debugAo;
}

void Scene::prepareAOGBuffer() {
    glViewport(0, 0, width_, height_);
    if (!glIsFramebuffer(FBO_)) {
        LOG(WARNING) << "generate FBO";
        glGenFramebuffers(1, &FBO_);
    }
    if (!ao_depth_map_) {
        ao_depth_map_ = make_shared<Texture2D>(GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_CLAMP_TO_BORDER,
                                               GL_CLAMP_TO_BORDER,
                                               GL_NEAREST,
                                               GL_NEAREST, GL_FLOAT);
        ao_depth_map_->generate(width_, height_, nullptr);
    }
    if (!ao_position_map_) {
        ao_position_map_ = make_shared<Texture2D>(GL_RGBA16F, GL_RGBA, GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST,
                                                  GL_FLOAT);
        ao_position_map_->generate(width_, height_, nullptr);
    }
    if (!ao_normal_map_) {
        ao_normal_map_ = make_shared<Texture2D>(GL_RGBA16F, GL_RGB, GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST,
                                                GL_FLOAT);
        ao_normal_map_->generate(width_, height_, nullptr);
    }
    if (!ao_albedoColor_map_) {
        ao_albedoColor_map_ = make_shared<Texture2D>(GL_RGBA, GL_RGBA, GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST,
                                                     GL_UNSIGNED_BYTE);
        ao_albedoColor_map_->generate(width_, height_, nullptr);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, FBO_);
    ao_depth_map_->bind(0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, ao_depth_map_->getId(), 0);
    ao_position_map_->bind(0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, ao_position_map_->getId(), 0);
    ao_normal_map_->bind(0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, ao_normal_map_->getId(), 0);
    ao_albedoColor_map_->bind(0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, ao_albedoColor_map_->getId(), 0);
    GLuint attachments[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
    glDrawBuffers(3, attachments);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOG(ERROR) << "frame buffer is not complete";
    }
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    for (const auto &object: objects_) {
        object->drawGBuffer(getCamera()->getViewMatrix(), getCamera()->getProjectionMatrix());
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Scene::debugAOBufferMap() {
    if (!debug_plane_) {
        debug_plane_ = make_shared<DebugPlane>(shared_from_this());
    }
    debug_fucntions_.push_back([=]() {
        debug_plane_->drawTexture(ao_depth_map_, DebugType::DebugType_Shadow);
    });
    debug_fucntions_.push_back([=]() {
        debug_plane_->drawTexture(ao_position_map_, DebugType::DebugType_RGB);
    });
    debug_fucntions_.push_back([=]() {
        debug_plane_->drawTexture(ao_normal_map_, DebugType::DebugType_RGB);
    });
    debug_fucntions_.push_back([=]() {
        debug_plane_->drawTexture(ao_albedoColor_map_, DebugType::DebugType_RGB);
    });
    debug_fucntions_.push_back([=](){
        debug_plane_->drawTexture(ssao_map_, DebugType::DebugType_R);
    });
    debug_fucntions_.push_back([=](){
        debug_plane_->drawTexture(ssao_blur_map_, DebugType::DebugType_R);
    });
}

void Scene::prepareAOMap() {
    if (ssao_kernel_.empty()) {
        // 生成ssao 向周围采样的
        std::uniform_real_distribution<float> random_float(0.0f, 1.0f); // 随机浮点数，数值大小范围为0.0~1.0
        std::default_random_engine generator;
        const int sample_num = 8;
        for (int i = 0; i < sample_num; ++i) {
            glm::vec3 sample(random_float(generator) * 2.0 - 1.0, random_float(generator) * 2.0 - 1.0,
                             random_float(generator));
            sample = glm::normalize(sample);
            sample *= random_float(generator);
            float scale = float(i) / float(sample_num);
            scale = lerp(0.1f, 1.0f, scale * scale);
            sample *= scale;
            ssao_kernel_.push_back(sample);
        }
    }
    if (ssao_noise_.empty()) {
        // 生成采样所需要的噪声
        const int noise_num = 16;
        std::uniform_real_distribution<float> random_float(0.0f, 1.0f); // 随机浮点数，数值大小范围为0.0~1.0
        std::default_random_engine generator;
        for (GLuint i = 0; i < 16; i++) {
            glm::vec3 noise(random_float(generator) * 2.0 - 1.0, random_float(generator) * 2.0 - 1.0, 0.0f);
            ssao_noise_.push_back(noise);
        }
        if (!ssao_noise_map_) {
            ssao_noise_map_ = make_shared<Texture2D>(GL_RGB16F, GL_RGB, GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST,
                                                     GL_FLOAT);
            ssao_noise_map_->generate(sqrt(noise_num), sqrt(noise_num), (unsigned char*)ssao_noise_.data());
        }
    }
    if (!ssao_map_) {
        ssao_map_ = make_shared<Texture2D>(GL_RGBA16F, GL_RGBA, GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST, GL_FLOAT);
        ssao_map_->generate(width_, height_, nullptr);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, FBO_);
    ssao_map_->bind(0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, ssao_map_->getId(), 0);
    GLuint attachments[] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, attachments);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOG(ERROR) << "frame buffer is not complete";
    }

    glViewport(0, 0, width_, height_);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    if (!debug_plane_) {
        debug_plane_ = make_shared<DebugPlane>(shared_from_this());
    }
    debug_plane_->prepareAOMap();
    glEnable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

uint32_t Scene::getWidth() const {
    return width_;
}

uint32_t Scene::getHeight() const {
    return height_;
}

const shared_ptr<Texture2D> &Scene::getAoPositionMap() const {
    return ao_position_map_;
}

const shared_ptr<Texture2D> &Scene::getAoNormalMap() const {
    return ao_normal_map_;
}

const shared_ptr<Texture2D> &Scene::getAoAlbedoColorMap() const {
    return ao_albedoColor_map_;
}

const vector<glm::vec3> &Scene::getSsaoKernel() const {
    return ssao_kernel_;
}

const vector<glm::vec3> &Scene::getSsaoNoise() const {
    return ssao_noise_;
}

const shared_ptr<Texture2D> &Scene::getSsaoNoiseMap() const {
    return ssao_noise_map_;
}

void Scene::blurAoMap() {
    if (!ssao_blur_map_) {
        ssao_blur_map_ = make_shared<Texture2D>(GL_RGBA16F, GL_RGBA, GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST, GL_FLOAT);
        ssao_blur_map_->generate(width_, height_, nullptr);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, FBO_);
    ssao_blur_map_->bind(0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, ssao_blur_map_->getId(), 0);
    GLuint attachments[] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, attachments);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOG(ERROR) << "frame buffer is not complete";
    }

    glViewport(0, 0, width_, height_);
    glDisable(GL_DEPTH_TEST);
    if (!debug_plane_) {
        debug_plane_ = make_shared<DebugPlane>(shared_from_this());
    }
    debug_plane_->blurTexture(ssao_map_, BlurType::BlurType_GaussianFiltering);
    glEnable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

