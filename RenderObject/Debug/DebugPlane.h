//
// Created by virgil on 2021/11/29.
//

#pragma once
#include <glew.h>
#include <memory>
#include <glm/glm.hpp>
#include "../BaseObject.h"

class Texture2D;
enum class DebugType{
    DebugType_Shadow = 0,
    DebugType_RGB = 1,
    DebugType_RGBA = 2,
    DebugType_R = 3,
    DebugType_G = 4,
    DebugType_B = 5,
    DebugType_A  =6
};

enum class BlurTargetType{
    BlurTargetType_R = 0,
    BlurTargetType_G = 1,
    BlurTargetType_B = 2,
    BlurTargetType_A = 3,
    BlurTargetType_RGB = 4,
    BlurTargetType_RGBA = 5
};

enum class BlurType{
    BlurType_GaussianFiltering, // 高斯滤波（模糊）
    BlurType_BilateralFiltering // 双边滤波（能更好的保存边界）
};


class DebugPlane : public BaseObject{
public:
    DebugPlane(std::shared_ptr<Scene> scene);
    ~DebugPlane() override;
    void draw() override;
    void update() override;
    void drawTexture(std::shared_ptr<Texture2D> texture, DebugType type);

    void prepareAOMap();

    void blurTexture(std::shared_ptr<Texture2D> texture, BlurTargetType target_type, BlurType blur_type);
private:
    /*
     * 构造VAO
     */
    void constructGeometry();
    uint32_t VAO_,VBO_;
};


