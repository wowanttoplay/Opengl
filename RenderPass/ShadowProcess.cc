//
// Created by virgil on 2021/6/13.
//

#include "ShadowProcess.h"
#include <iostream>

using namespace std;

const uint32_t kShadowWidth = 1024, kShadowHeight = 1024;

ShadowProcess::ShadowProcess() {
    // frame buffer
    glGenFramebuffers(1, &this->depth_map_FBO_);
    glBindFramebuffer(GL_FRAMEBUFFER, this->depth_map_FBO_);
    // cube texture
    glGenTextures(1, &this->depth_cube_texture_);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->depth_cube_texture_);
    for (int i = 0; i < 6; ++i) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, kShadowWidth, kShadowWidth, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
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
}


