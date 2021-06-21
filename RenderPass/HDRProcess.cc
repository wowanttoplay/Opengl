//
// Created by virgil on 2021/6/20.
//

#include "HDRProcess.h"
#include "../Log/LogUtil.h"
#include "../Data/vertex_data.h"
#include "../ResourceManager.h"

void HDRProcess::PreRender(HDRProcess::RenderFunc render_func) {
    glBindFramebuffer(GL_FRAMEBUFFER, this->FBO_);
    render_func();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void HDRProcess::SecondRender() {
    Shader shader = ResourceManager::GetShader("basic_quad");
    shader.Use();
    shader.SetFloat("exposure", exposure_);
    shader.SetFloat("gamma", gamma_);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture_);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindVertexArray(this->VAO_);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

HDRProcess::HDRProcess() {
    InitFBO();
    InitVAO();
    Shader shader = ResourceManager::LoadShader("../Data/basic_quad.vs", "../Data/basic_quad.fs", nullptr,
                                                "basic_quad");
    shader.Use();
    shader.SetInteger("hdrTexture", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture_);
    shader.SetInteger("b_dbr", true);

}

void HDRProcess::InitVAO() {
    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);
    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(RenderData::basic_quad), RenderData::basic_quad, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void *) (sizeof(GL_FLOAT) * 3));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void HDRProcess::InitFBO() {
    glGenFramebuffers(1, &this->FBO_);
    // texture
    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 1024, 1024, 0, GL_RGB, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 1024);

    glBindFramebuffer(GL_FRAMEBUFFER, FBO_);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        logE("frame buffer is not complete");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void HDRProcess::SetExposure(float exposure) {
    exposure_ = exposure;
}

void HDRProcess::SetGamma(float gamma) {
    gamma_ = gamma;
}
