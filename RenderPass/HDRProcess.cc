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

void HDRProcess::HDRRender() {
    glViewport(0, 0, width_, height_);
    glClearColor(1.0, 0.0, 0.0, 1.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Shader shader = ResourceManager::GetShader("basic_quad");
    shader.Use();
    shader.SetFloat("exposure", exposure_);
    shader.SetFloat("gamma", gamma_);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->float_color_texture_);
    glBindVertexArray(this->VAO_);
//    glDrawArrays(GL_LINE_STRIP, 0, 4);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void HDRProcess::BrightColorRender() {
    // 将亮色的texture绑定到framebuffer上，draw call来初始化亮色texture
    glBindFramebuffer(GL_FRAMEBUFFER, this->bright_FBO_);
    glClearColor(0.0, 1.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // 绘制
    Shader shader = ResourceManager::GetShader("basic_quad");
    shader.Use();
    shader.SetInteger("b_bright", true);
    HDRRender();
    shader.SetInteger("b_bright", false);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

HDRProcess::HDRProcess(float width, float height) {
    this->width_ = width;
    this->height_ = height;
    InitHDRFBO();
    InitVAO();
    InitShader();
    InitBrightFBO();
    InitBlurFBO();
}

void HDRProcess::InitBlurFBO() {// 高斯模糊
    glGenFramebuffers(2, blurFBO_);
    glGenTextures(2, blur_color_texture_);
    for (int i = 0; i < 2; ++i) {
        glBindFramebuffer(GL_FRAMEBUFFER, blurFBO_[i]);
        glBindTexture(GL_TEXTURE_2D, blur_color_texture_[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->width_, this->height_, 0, GL_RGB, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, blur_color_texture_[i], 0);
    }
}

void HDRProcess::InitBrightFBO() {//初始化亮色texture
    glGenFramebuffers(1, &this->bright_FBO_);
    glBindFramebuffer(GL_FRAMEBUFFER, this->bright_FBO_);
    InitFloatTexture(bright_color_texture_);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, bright_color_texture_, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        logE("bright frame buffer is not complete");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void HDRProcess::InitFloatTexture(GLuint &texture) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    logE("init float texture, width:%f, height:%f", this->width_, this->height_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->width_, this->height_, 0, GL_RGB, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void HDRProcess::InitShader() {
    // hdr渲染使用着色器
    Shader shader = ResourceManager::LoadShader("../Data/basic_quad.vs", "../Data/basic_quad.fs", nullptr,
                                                "basic_quad");
    shader.Use();
    shader.SetInteger("b_blur", false);
    shader.SetInteger("hdrTexture", 0);
    shader.SetInteger("blurTexture", 1);
    // 高斯模糊所用着色器
    Shader blur_shader = ResourceManager::LoadShader("../Data/basic_quad.vs", "../Data/blur.fs", nullptr, "blur");
    blur_shader.Use();
    blur_shader.SetInteger("texture0", 0);
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

void HDRProcess::InitHDRFBO() {
    glGenFramebuffers(1, &this->FBO_);
    // texture
    InitFloatTexture(this->float_color_texture_);
    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width_, height_);

    glBindFramebuffer(GL_FRAMEBUFFER, FBO_);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, float_color_texture_, 0);
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

void HDRProcess::BrightColorDebugRender() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    Shader shader = ResourceManager::GetShader("basic_quad");
    shader.Use();
    shader.SetFloat("exposure", exposure_);
    shader.SetFloat("gamma", gamma_);
    shader.SetInteger("b_blur", false);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->bright_color_texture_);
    glBindVertexArray(this->VAO_);
//    glDrawArrays(GL_LINE_STRIP, 0, 4);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void HDRProcess::BlurProcess() {
    bool horizontal = true, first_draw = true;
    Shader shader = ResourceManager::GetShader("blur");
    shader.Use();

    for (int i = 0; i < 10; ++i) {
        glBindFramebuffer(GL_FRAMEBUFFER, this->blurFBO_[horizontal]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.SetInteger("b_horizontal", horizontal);
        // 第一次的时候勇bright texture，后面就是用另一个模糊纹理
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, first_draw ? bright_color_texture_ : this->blur_color_texture_[!horizontal]);
        glBindVertexArray(this->VAO_);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
        first_draw = false;
        horizontal = !horizontal;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void HDRProcess::BlurDebugRender() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Shader shader = ResourceManager::GetShader("basic_quad");
    shader.Use();
    shader.SetFloat("exposure", exposure_);
    shader.SetFloat("gamma", gamma_);
    shader.SetInteger("b_bright", false);
    shader.SetInteger("b_blur", false);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->blur_color_texture_[1]);
    glBindVertexArray(this->VAO_);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//    glDrawArrays(GL_LINE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void HDRProcess::FloodLightRender() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Shader shader = ResourceManager::GetShader("basic_quad");
    shader.Use();
    shader.SetFloat("exposure", exposure_);
    shader.SetFloat("gamma", gamma_);
    shader.SetInteger("b_blur", true);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->float_color_texture_);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, this->blur_color_texture_[1]);
    glBindVertexArray(this->VAO_);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
    shader.SetInteger("b_blur", false);
}

void HDRProcess::SetViewSize(uint32_t width, uint32_t height) {
    this->width_ = width;
    this->height_ = height;
}


