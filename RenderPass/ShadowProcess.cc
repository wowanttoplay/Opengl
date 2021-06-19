//
// Created by virgil on 2021/6/13.
//

#include "ShadowProcess.h"
#include <iostream>
#include <string>
#include <vector>
#include "../ResourceManager.h"
#include "../Log/LogUtil.h"

using namespace std;


const uint32_t kShadowWidth = 1024, kShadowHeight = 1024;


ShadowProcess::ShadowProcess() {
    PrePareResource(this->depth_map_FBO_, this->depth_cube_map_);
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
//    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
//    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
//    glDrawBuffer(GL_NONE);
//    glReadBuffer(GL_NONE);
//    // check frame buffer
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
//        logE("frame buffer not complete");
//    }
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowProcess::Render(FuncOfShadow render_func) {
    // prepare view and projection matrix
    float aspect = (float) kShadowWidth / (float) kShadowHeight;
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspect, this->near_,this->far_);
    std::vector<glm::mat4> view_vec;
    view_vec.push_back(glm::lookAt(light_position_, light_position_ + glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
    view_vec.push_back(glm::lookAt(light_position_, light_position_ + glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
    view_vec.push_back(glm::lookAt(light_position_, light_position_ + glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)));
    view_vec.push_back(glm::lookAt(light_position_, light_position_ + glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)));
    view_vec.push_back(glm::lookAt(light_position_, light_position_ + glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
    view_vec.push_back(glm::lookAt(light_position_, light_position_ + glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f)));

    // render 6 times, finished the shadow cube map
    glViewport(0, 0, kShadowWidth, kShadowHeight);
    glBindFramebuffer(GL_FRAMEBUFFER, this->depth_map_FBO_);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    for (int i =0; i < 6; ++i) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, this->depth_cube_map_, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        render_func(view_vec.at(i), projection);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


