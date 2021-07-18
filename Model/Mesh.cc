//
// Created by virgil on 2021/7/12.
//

#include "Mesh.h"

using namespace std;


void Mesh::Render(Shader shader) {
    shader.Use();
    SetShaderAttributes(shader, "albedo");
    SetShaderAttributes(shader, "normal");
    SetShaderAttributes(shader, "metallic");
    SetShaderAttributes(shader, "roughness");
    SetShaderAttributes(shader, "ao");

    glBindVertexArray(this->VAO_);
    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::SetShaderAttributes(Shader &shader, const string name) {
    shader.SetVector3f(name.c_str(), material_[name]->data);
    if (material_["albedo"]->texture) {
        glActiveTexture(GL_TEXTURE0);
        material_["albedo"]->texture->Bind();
        shader.SetInteger(("b_" + name + "_texture").c_str(), GL_TRUE);
    } else {
        shader.SetInteger(("b_" + name + "_texture").c_str(), GL_FALSE);
    }
}

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices,
           const std::map<std::string, shared_ptr<Material>> &metarial) : vertices_(vertices), indices_(indices),
                                                                          material_(metarial) {
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