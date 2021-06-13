//
// Created by virgil on 2021/6/13.
//

#include "ShadowProcess.h"
#include <iostream>
#include <string>
#include <vector>
#include "../ResourceManager.h"

using namespace std;

const uint32_t kShadowWidth = 1024, kShadowHeight = 1024;
const std::string kShadowShaderName = "shadow";

ShadowProcess::ShadowProcess() {
    // frame buffer
    glGenFramebuffers(1, &this->depth_map_FBO_);
    glBindFramebuffer(GL_FRAMEBUFFER, this->depth_map_FBO_);
    // cube texture
    glGenTextures(1, &this->depth_cube_texture_);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->depth_cube_texture_);
    for (int i = 0; i < 6; ++i) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, kShadowWidth, kShadowWidth, 0,
                     GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // frame buffer bind texture
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, this->depth_cube_texture_, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // init shader
    this->shader_ = ResourceManager::LoadShader("../Data/shadow_map.vs", "../Data/shadow_map.fs",
                                                "../Data/shadow_map.gs",
                                                kShadowShaderName);
    this->shader_.Use();
    this->shader_.SetInteger("depthMap",1);
}

void ShadowProcess::FirstRender() {
    glViewport(0, 0, kShadowWidth, kShadowHeight);
    glBindFramebuffer(GL_BUFFER, this->depth_map_FBO_);
    glClear(GL_DEPTH_BUFFER_BIT);
    ConfigShaderAndMatrix();
}

void ShadowProcess::ConfigShaderAndMatrix() {
    // calculate shaodw projection
    float aspect = (float) kShadowWidth / (float) kShadowHeight;
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspect, this->near_, this->far_);
    // calculate View * projection of cube shadow
    vector<glm::mat4> shadow_transform;
    shadow_transform.push_back(projection *
                               glm::lookAt(this->light_position_, this->light_position_ + glm::vec3(1.0, 0.0, 0.0),
                                           glm::vec3(0.0, -1.0, 0.0)));
    shadow_transform.push_back(projection *
                               glm::lookAt(this->light_position_, this->light_position_ + glm::vec3(-1.0, 0.0, 0.0),
                                           glm::vec3(0.0, -1.0, 0.0)));
    shadow_transform.push_back(projection *
                               glm::lookAt(this->light_position_, this->light_position_ + glm::vec3(0.0, 1.0, 0.0),
                                           glm::vec3(0.0, 0.0, 1.0)));
    shadow_transform.push_back(projection *
                               glm::lookAt(this->light_position_, this->light_position_ + glm::vec3(0.0, -1.0, 0.0),
                                           glm::vec3(0.0, 0.0, -1.0)));
    shadow_transform.push_back(projection *
                               glm::lookAt(this->light_position_, this->light_position_ + glm::vec3(0.0, 0.0, 1.0),
                                           glm::vec3(0.0, -1.0, 0.0)));
    shadow_transform.push_back(projection *
                               glm::lookAt(this->light_position_, this->light_position_ + glm::vec3(0.0, 0.0, -1.0),
                                           glm::vec3(0.0, -1.0, 0.0)));


}

void ShadowProcess::SecondRender() {
    glViewport(0, 0, this->width_, this->height_);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ConfigShaderAndMatrix();
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->depth_cube_texture_);
}

void ShadowProcess::SetScreenSize(int width, int height) {
    this->width_ = width;
    this->height_ = height;
}

void ShadowProcess::SetNearAndFar(float near, float far) {
    this->near_ = near;
    this->far_ = far;
}

void ShadowProcess::SetLightPosition(const glm::vec3 light_position) {
    this->light_position_ = light_position;
}


