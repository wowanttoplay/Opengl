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


ShadowProcess::ShadowProcess() {
    PrePareResource(this->depth_map_FBO_, this->depth_cube_texture_);
}

// 准备好渲染阴影贴图的shader和相关设置
void ShadowProcess::FirstRender(Shader shader) {
    glViewport(0, 0, kShadowWidth, kShadowHeight);
    glBindFramebuffer(GL_FRAMEBUFFER, this->depth_map_FBO_);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ConfigShaderAndMatrix(shader);
}

void ShadowProcess::ConfigShaderAndMatrix(Shader shader) {
    // calculate shaodw projection
    float aspect = (float) kShadowWidth / (float) kShadowHeight;
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspect, this->near_,this->far_);
    // calculate View * projection of cube shadow
    std::vector<glm::mat4> shadowTransforms;
    shadowTransforms.push_back(projection * glm::lookAt(light_position_, light_position_ + glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
    shadowTransforms.push_back(projection * glm::lookAt(light_position_, light_position_ + glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
    shadowTransforms.push_back(projection * glm::lookAt(light_position_, light_position_ + glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)));
    shadowTransforms.push_back(projection * glm::lookAt(light_position_, light_position_ + glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)));
    shadowTransforms.push_back(projection * glm::lookAt(light_position_, light_position_ + glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
    shadowTransforms.push_back(projection * glm::lookAt(light_position_, light_position_ + glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
    //set shader
    shader.Use();
    for (int i = 0; i < 6; ++i) {
        string mat_name = "shadowMatrices[" + to_string(i) + "]";
        shader.SetMatrix4(mat_name.c_str(), shadowTransforms[i]);
    }
    shader.SetFloat("far_plane", this->far_);
    shader.SetVector3f("light_position", this->light_position_);
}

// 准备好阴影渲染的环境
void ShadowProcess::SecondRender() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, this->screen_width_, this->screen_height_);
    glClearColor(0.2, 0.2 ,0.2 ,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ShadowProcess::SetScreenSize(int width, int height) {
    this->screen_width_ = width;
    this->screen_height_ = height;
}

void ShadowProcess::SetNearAndFar(float near, float far) {
    this->near_ = near;
    this->far_ = far;
}

void ShadowProcess::SetLightPosition(const glm::vec3 light_position) {
    this->light_position_ = light_position;
}

void ShadowProcess::PrePareResource(unsigned int& FBO, unsigned int& texture) {
    glGenFramebuffers(1, &FBO);
//    // create depth cubemap texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    for (unsigned int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, kShadowWidth, kShadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


