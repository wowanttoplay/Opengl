//
// Created by virgil on 2021/6/12.
//

#pragma once
#include <glm/glm.hpp>
#include <tuple>
#include <vector>
#include <memory>
#include "BaseObject.h"

class Sphere : public BaseObject {
public:
    Sphere(std::shared_ptr<Scene>scene, const glm::vec3& scale, const  glm::vec3& position, int x_num, int y_num);
    ~Sphere() override;

    void drawDepthMap(const glm::mat4 &view, const glm::mat4 &projection) override;
    void draw() override;
    void update() override;

    /**
     * 绘制纯色object
     */
    void drawSimpleColor();

    void drawGBuffer(const glm::mat4 &view, const glm::mat4 &projection) override;

private:
    void constructGeometry();
private:
    uint32_t VAO_,VBO_,EBO_;
    uint32_t x_num_, y_num_;
    std::vector<float>vertices_data;
    std::vector<uint32_t> indices_data;

    /**
     * 带阴影的phong模型
     */
    void drawShadowPhong();

    /**
     * 简单的phong模型着色
     */
    void drawSimplePhong();
};

