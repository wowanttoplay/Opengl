//
// Created by virgil on 2021/6/14.
//
#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <functional>

#include "../Shader.h"



class ColorCubeProcess {
    using RenderFunc = std::function<void(glm::mat4 , glm::mat4)>;
public:
    GLuint color_cube_map_; //生成颜色cube
    GLuint color_FBO;   //  颜色帧缓冲
    /**
     *
     * @param width 宽
     * @param height 高（如果是cube的话，宽和高实际应该是一样的）
     * @param b_mipmap 是否开启多级纹理
     */
    ColorCubeProcess(float width, float height, bool b_mipmap = false);
    /**
     *
     * @param near 近平面
     * @param far 远平面
     */
    void SetNearAndFar(float near, float far);
    /**
     *
     * @param center cube中心位置
     */
    void SetCenter(const glm::vec3& center);
    /**
     *
     * @param FBO 要绑定的FBO
     * @param texture 要生成的纹理
     * @param b_mipmap 是否要生成多级纹理
     * TODO:这个函数应该是可以单独拉出来的工具函数，没必要写在这里
     */
    void PrePareResource(GLuint &FBO, GLuint &texture, bool b_mipmap);
    /**
     *
     * @param render_func 渲染时调用的函数，里面应该包含cube里要包含的所有渲染对象的渲染
     */
    void Render(RenderFunc render_func, uint8_t mipmap_level);

private:
    float screen_width_, screen_height_; // 屏幕大小
    float near_, far_;  //远、近平面
    glm::vec3 center_; // cube map 生成时的中心位置
    bool b_mipmap_ = false;
};

