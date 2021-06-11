//
// Created by virgil on 2021/6/11.
//

#include "Box.h"
#include "../Data/vertex_data.h"

Box::Box() {
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER,  sizeof(RenderData::boxVertices), RenderData::boxVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Box::Render(Shader shader, Texture2D texture, const glm::mat4 &model, const glm::mat4 &view,
                 const glm::mat4 &projection) {

    shader.Use();
    shader.SetMatrix4("model", model);
    shader.SetMatrix4("view",view);
    shader.SetMatrix4("projection", projection);

    glActiveTexture(GL_TEXTURE0);
    shader.SetInteger("texture0", 0);
    texture.Bind();

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDrawArrays(GL_LINES, 0, 36);
}
