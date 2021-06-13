//
// Created by virgil on 2021/6/10.
//

#include "Plane.h"
#include "../Data/vertex_data.h"
#include "../Log/LogUtil.h"

Plane::Plane() {
    // generate VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // generate VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(RenderData::planeVertices), RenderData::planeVertices, GL_STATIC_DRAW);
    // attrib pointer
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // unload
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // prepare
}

void Plane::Render(Shader shader) {
    shader.Use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Plane::Update(float dt) {
}


