//
// Created by virgil on 2021/6/14.
//

#include "MirrorProcess.h"
#include <vector>
#include <string>

#include "../Log/LogUtil.h"

using namespace std;

MirrorProcess::MirrorProcess() {
    PrePareResource(this->color_FBO, this->color_cube_map_);
}

void MirrorProcess::FirstRender(Shader &shader) {
    glViewport(0, 0, this->screen_width_, this->screen_height_);
    glBindFramebuffer(GL_FRAMEBUFFER, this->color_FBO);
    glClearColor(0.1, 0.1, 0.1, 0.1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ConfigShaderAndMatrix(shader);
}

void MirrorProcess::SecondRender(Shader &shader) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, this->screen_width_, this->screen_height_);
    glClearColor(0.1, 0.1, 0.1, 0.1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MirrorProcess::SetNearAndFar(int near, int far) {
    this->near_ = near;
    this->far_ = far;
}

void MirrorProcess::SetCenter(const glm::vec3 &center) {
    this->center_ = center;
}

void MirrorProcess::ConfigShaderAndMatrix(Shader &shader) {
    // calculate shaodw projection
    float aspect = (float) this->screen_width_ / (float) this->screen_height_;
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspect, this->near_, this->far_);
    // calculate View * projection of cube shadow
    vector<glm::mat4> shadowTransforms;
    shadowTransforms.push_back(projection * glm::lookAt(center_, center_ + glm::vec3(1.0f, 0.0f, 0.0f),
                                                        glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(projection * glm::lookAt(center_, center_ + glm::vec3(-1.0f, 0.0f, 0.0f),
                                                        glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(projection * glm::lookAt(center_, center_ + glm::vec3(0.0f, 1.0f, 0.0f),
                                                        glm::vec3(0.0f, 0.0f, 1.0f)));
    shadowTransforms.push_back(projection * glm::lookAt(center_, center_ + glm::vec3(0.0f, -1.0f, 0.0f),
                                                        glm::vec3(0.0f, 0.0f, -1.0f)));
    shadowTransforms.push_back(projection * glm::lookAt(center_, center_ + glm::vec3(0.0f, 0.0f, 1.0f),
                                                        glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(projection * glm::lookAt(center_, center_ + glm::vec3(0.0f, 0.0f, -1.0f),
                                                        glm::vec3(0.0f, -1.0f, 0.0f)));
    //set shader
    shader.Use();
    for (int i = 0; i < 6; ++i) {
        string mat_name = "shadowMatrices[" + to_string(i) + "]";
        shader.SetMatrix4(mat_name.c_str(), shadowTransforms[i]);
    }
}

void MirrorProcess::PrePareResource(GLuint &FBO, GLuint &texture) {
    // 生成fbo，同时绑定颜色贴图，此外也要绑一个深度
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    for (unsigned int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, this->screen_width_, this->screen_height_, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // attach color buffer
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
    // bind depth buffer
    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->screen_width_,this->screen_height_);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    if (glCheckFramebufferStatus(FBO) != GL_FRAMEBUFFER_COMPLETE) {
        logE("frame buffer not complete");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
