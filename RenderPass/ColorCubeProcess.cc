//
// Created by virgil on 2021/6/14.
//

#include "ColorCubeProcess.h"
#include <vector>
#include <string>

#include "../Log/LogUtil.h"

using namespace std;

const int kColor_texture_size = 1024;

ColorCubeProcess::ColorCubeProcess() {
    PrePareResource(this->color_FBO, this->color_cube_map_);
}

void ColorCubeProcess::FirstRender(Shader &shader) {
    glViewport(0, 0, kColor_texture_size, kColor_texture_size);
    glBindFramebuffer(GL_FRAMEBUFFER, this->color_FBO);
//glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.1, 0.1, 0.1, 0.1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ConfigShaderAndMatrix(shader);
}

void ColorCubeProcess::SecondRender(Shader &shader) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, this->screen_width_, this->screen_height_);
    glClearColor(0.1, 0.1, 0.1, 0.1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ColorCubeProcess::SetNearAndFar(float near, float far) {
    this->near_ = near;
    this->far_ = far;
}

void ColorCubeProcess::SetCenter(const glm::vec3 &center) {
    this->center_ = center;
}

void ColorCubeProcess::ConfigShaderAndMatrix(Shader &shader) {
    // calculate projection
    float aspect = (float) this->screen_width_ / (float) this->screen_height_;
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspect, this->near_, this->far_);
    // calculate View * projection
    vector<glm::mat4> Transforms;
    Transforms.push_back(projection * glm::lookAt(center_, center_ + glm::vec3(1.0f, 0.0f, 0.0f),
                                                  glm::vec3(0.0f, -1.0f, 0.0f)));
    Transforms.push_back(projection * glm::lookAt(center_, center_ + glm::vec3(-1.0f, 0.0f, 0.0f),
                                                  glm::vec3(0.0f, -1.0f, 0.0f)));
    Transforms.push_back(projection * glm::lookAt(center_, center_ + glm::vec3(0.0f, 1.0f, 0.0f),
                                                  glm::vec3(0.0f, 0.0f, 1.0f)));
    Transforms.push_back(projection * glm::lookAt(center_, center_ + glm::vec3(0.0f, -1.0f, 0.0f),
                                                  glm::vec3(0.0f, 0.0f, -1.0f)));
    Transforms.push_back(projection * glm::lookAt(center_, center_ + glm::vec3(0.0f, 0.0f, 1.0f),
                                                  glm::vec3(0.0f, -1.0f, 0.0f)));
    Transforms.push_back(projection * glm::lookAt(center_, center_ + glm::vec3(0.0f, 0.0f, -1.0f),
                                                  glm::vec3(0.0f, -1.0f, 0.0f)));
    //set shader
    shader.Use();
    for (int i = 0; i < 6; ++i) {
        string mat_name = "mirrorMatrices[" + to_string(i) + "]";
        shader.SetMatrix4(mat_name.c_str(), Transforms[i]);
    }
}

void ColorCubeProcess::PrePareResource(GLuint &FBO, GLuint &texture) {
    // 生成fbo，同时绑定颜色贴图，此外也要绑一个深度
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    // texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    // 绑定浮点缓冲，后面HDR要用
    for (unsigned int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, kColor_texture_size, kColor_texture_size, 0,
                     GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // attach color buffer
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
     logE("error : %d", glGetError());
//     bind depth and stencil buffer
    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, kColor_texture_size,kColor_texture_size);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    logE("error : %d", glGetError());

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        logE("frame buffer not complete");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ColorCubeProcess::SetScreenSize(int width, int height) {
    this->screen_width_ = width;
    this->screen_height_ = height;
}

void ColorCubeProcess::Render(RenderFunc render_func) {
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

    glViewport(0, 0, this->screen_width_, this->screen_height_);
    glBindFramebuffer(GL_FRAMEBUFFER, this->color_FBO);
    for (int i =0; i < 6; ++i) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, this->color_cube_map_, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        render_func(view_vec.at(i), projection);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


