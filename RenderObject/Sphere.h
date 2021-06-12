//
// Created by virgil on 2021/6/12.
//

#pragma once
#include <glm/glm.hpp>
#include <tuple>
#include <vector>

#include "../Texture2D.h"
#include "../Shader.h"


struct Point{
    float x_;
    float y_;
    float z_;
    Point(float x, float y ,float z) : x_(x), y_(y), z_(z){}
};

struct TriangleIndices{
    uint32_t first_;
    uint32_t second_;
    uint32_t third_;
    TriangleIndices(uint32_t first, uint32_t second, uint32_t third) : first_(first), second_(second), third_(third){}
};

class Sphere {
public:
    virtual ~Sphere();
    inline void SetColor(const glm::vec4 color){this->color = color;};
    explicit Sphere(int x_num, int y_num);
    void Render(Shader shader, Texture2D texture, const glm::mat4 &model, const glm::mat4 &view,
                const glm::mat4 &projection);
private:
    uint32_t VAO,VBO,EBO;
    glm::vec4 color;
    std::vector<float>vertices_data;
    std::vector<uint32_t> indices_data;
};

