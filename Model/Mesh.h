//
// Created by virgil on 2021/7/12.
//

#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <map>

#include "../Texture2D.h"
#include "../Shader.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture_coords;
};

class Mesh {
public:
    Mesh(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices,
         const std::map<std::string,std::shared_ptr<Texture2D>> &textures);

    void Render(Shader shader);
private:
    std::vector<Vertex> vertices_;
    std::vector<uint32_t> indices_;
    std::map<std::string, std::shared_ptr<Texture2D>> textures_;

    GLuint VAO_, VBO_, EBO_;
    /**
     * 初始化VAO、VBO、EBO
     */
    void InitVAO();
};



