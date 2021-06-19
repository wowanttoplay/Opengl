//
// Created by virgil on 2021/6/12.
//

#include "Sphere.h"
#include "../Log/LogUtil.h"
#include "../Tool/PrintTool.h"

using namespace std;

Sphere::Sphere(int x_num, int y_num) {
    // 生成球面顶点数据
    for (int y = 0; y <= y_num; y++) {
        for (int x = 0; x <= x_num; x++) {
            float xSegment = (float) x / (float) x_num;
            float ySegment = (float) y / (float) x_num;
            float xPos = std::cos(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);
            float yPos = std::cos(ySegment * M_PI);
            float zPos = std::sin(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);
             // 坐标
            vertices_data.push_back(xPos);
            vertices_data.push_back(yPos);
            vertices_data.push_back(zPos);
            // 法线
            vertices_data.push_back(xPos);
            vertices_data.push_back(yPos);
            vertices_data.push_back(zPos);
            // 纹理
            vertices_data.push_back(xSegment);
            vertices_data.push_back(ySegment);
        }
    }

    //生成球的Indices
    for (int i = 0; i < y_num; i++) {
        for (int j = 0; j < x_num; j++) {
            indices_data.push_back(i * (x_num + 1) + j);
            indices_data.push_back((i + 1) * (x_num + 1) + j);
            indices_data.push_back((i + 1) * (x_num + 1) + j + 1);
            indices_data.push_back(i * (x_num + 1) + j);
            indices_data.push_back((i + 1) * (x_num + 1) + j + 1);
            indices_data.push_back(i * (x_num + 1) + j + 1);
        }
    }

    // 绑定数据
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);
    // VBO
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_data.size() * sizeof(float), &vertices_data[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(GL_FLOAT)));
    // EBO;
    glGenBuffers(1, &this->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_data.size() * sizeof(uint32_t), &indices_data[0], GL_STATIC_DRAW);
    //unload
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Sphere::Render(Shader shader) {
    shader.Use();
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, indices_data.size(), GL_UNSIGNED_INT, 0);
}

Sphere::~Sphere() {

}


