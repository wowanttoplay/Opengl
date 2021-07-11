//
// Created by virgil on 2021/7/11.
//

#include "BasicQuadProcess.h"
#include "../Log/LogUtil.h"
#include "../Data/vertex_data.h"

BasicQuadProcess::BasicQuadProcess(float width, float height) : width_(width), height_(height) {
    InitFBO();
}

void BasicQuadProcess::InitFBO() {
    glGenFramebuffers(1, &this->FBO_);
    this->texture_.Generate(width_, height_, (float *) 0);
    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width_, height_);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO_);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_.ID, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        logE("frame buffer is not complete");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void BasicQuadProcess::Render(BasicQuadProcess::RenderFunc render_func) {
    glBindFramebuffer(GL_FRAMEBUFFER, this->FBO_);
    glViewport(0, 0, width_, height_);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    render_func();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

