//
// Created by virgil on 2021/6/14.
//

#include "ColorCubeProcess.h"
#include <vector>
#include <string>

#include "../Log/LogUtil.h"

using namespace std;

ColorCubeProcess::ColorCubeProcess(float width, float height, bool b_mipmap) {
    this->screen_width_ = width;
    this->screen_height_ = height;
    this->b_mipmap_ = b_mipmap;
    PrePareResource(this->color_FBO, this->color_cube_map_, this->b_mipmap_);
}


void ColorCubeProcess::SetNearAndFar(float near, float far) {
    this->near_ = near;
    this->far_ = far;
}

void ColorCubeProcess::SetCenter(const glm::vec3 &center) {
    this->center_ = center;
}

void ColorCubeProcess::PrePareResource(GLuint &FBO, GLuint &texture, bool b_mipmap) {
    // 生成fbo，同时绑定颜色贴图，此外也要绑一个深度
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    // texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    // 绑定浮点缓冲，后面HDR要用
    for (unsigned int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, screen_width_, screen_height_, 0,
                     GL_RGB, GL_FLOAT, NULL);
    if (b_mipmap) {
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    }else {
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // attach color buffer
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
//     logE("error : %d", glGetError());
//     bind depth and stencil buffer
    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, screen_width_, screen_height_);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ColorCubeProcess::Render(RenderFunc render_func, uint8_t mipmap_level) {
    float aspect = (float) this->screen_width_ / (float) this->screen_height_;
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspect, this->near_, this->far_);
    // calculate View * projection
    vector<glm::mat4> view_vec;
    view_vec.push_back(glm::lookAt(center_, center_ + glm::vec3(1.0f, 0.0f, 0.0f),
                                   glm::vec3(0.0f, -1.0f, 0.0f)));
    view_vec.push_back(glm::lookAt(center_, center_ + glm::vec3(-1.0f, 0.0f, 0.0f),
                                   glm::vec3(0.0f, -1.0f, 0.0f)));
    view_vec.push_back(glm::lookAt(center_, center_ + glm::vec3(0.0f, 1.0f, 0.0f),
                                   glm::vec3(0.0f, 0.0f, 1.0f)));
    view_vec.push_back(glm::lookAt(center_, center_ + glm::vec3(0.0f, -1.0f, 0.0f),
                                   glm::vec3(0.0f, 0.0f, -1.0f)));
    view_vec.push_back(glm::lookAt(center_, center_ + glm::vec3(0.0f, 0.0f, 1.0f),
                                   glm::vec3(0.0f, -1.0f, 0.0f)));
    view_vec.push_back(glm::lookAt(center_, center_ + glm::vec3(0.0f, 0.0f, -1.0f),
                                   glm::vec3(0.0f, -1.0f, 0.0f)));
    //set shader
    if (!this->b_mipmap_) {
        mipmap_level = 0;
    }
    float mipmap_scale = pow(0.5, mipmap_level);
    // 不同的mipmap级别，要渲染的大小不一样
    glViewport(0, 0, this->screen_width_ * mipmap_scale, this->screen_height_ * mipmap_scale);

    glBindFramebuffer(GL_FRAMEBUFFER, this->color_FBO);
    for (int i = 0; i < 6; ++i) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                               this->color_cube_map_, mipmap_level);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        render_func(view_vec.at(i), projection);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


