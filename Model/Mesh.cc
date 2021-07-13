//
// Created by virgil on 2021/7/12.
//

#include "Mesh.h"

using namespace std;


void Mesh::Render(Shader shader) {
    shader.Use();
    // 纹理绑定，和shader相关
    for (int i = 0; i < textures_.size(); ++i) {
        const string &type_name = textures_.at(i)->name;
        if (type_name == "base_color") {
            glActiveTexture(GL_TEXTURE0);
            textures_.at(i)->Bind();
        } else if (type_name == "roughness") {
            glActiveTexture(GL_TEXTURE1);
            textures_.at(i)->Bind();
        } else if (type_name == "normal") {
            glActiveTexture(GL_TEXTURE2);
            textures_.at(i)->Bind();
        } else if (type_name == "metal") {
            glActiveTexture(GL_TEXTURE3);
            textures_.at(i)->Bind();
        }
    }
    glBindVertexArray(this->VAO_);
    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices,
           const std::vector<shared_ptr<Texture2D>> &textures) : vertices_(vertices), indices_(indices),
                                                                 textures_(textures) {
    InitVAO();
}

void Mesh::InitVAO() {
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);

    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex), vertices_.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(uint32_t), indices_.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, texture_coords));

    glBindVertexArray(0);
}