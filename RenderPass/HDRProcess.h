//
// Created by virgil on 2021/6/20.
//

#pragma once

#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <functional>

class HDRProcess {
public:
    using RenderFunc = std::function<void()>;

    HDRProcess();

    void PreRender(RenderFunc render_func);

    /**
     * 用来进行HDR绘制
     */
    void HDRRender();

    /*
     * 用来初始化亮色纹理
     * */
    void BrightColorRender();
    /**
     * 用来显示亮色纹理，便于调试
     */
    void BrightColorDebugRender();
    /**
     * 高斯模糊处理亮色区域，得到模糊处理后的纹理
     */
    void BlurProcess();
    /**
     * 高斯模糊的结果查看
     */
     void BlurDebugRender();
    /**
     * 泛光渲染,需要准备好hdr和blur纹理
     */
     void FloodLightRender();

    // 设置gamma值
    void SetGamma(float gamma);
    inline float Getgamma() {return gamma_;}

    // 设置曝光值
    void SetExposure(float exposure);
    inline float GetExposure() {return exposure_;}

private:
    GLuint FBO_, float_color_texture_;  //HDR本身
    GLuint bright_FBO_, bright_color_texture_;  //亮色区域相关
    GLuint blurFBO_[2], blur_color_texture_[2]; // 高斯模糊相关
    GLuint VAO_, VBO_;
    float gamma_ = 1.0f;
    float exposure_ = 0.5f;

    void InitHDRFBO();
    void InitVAO();
    void InitShader();

    void InitFloatTexture(GLuint &texture) ;

    void InitBrightFBO() ;

    void InitBlurFBO() ;
};

