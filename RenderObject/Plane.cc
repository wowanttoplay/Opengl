//
// Created by virgil on 2021/6/10.
//

#include "Plane.h"
#include "../Data/vertex_data.h"
#include "../ResourceManager.h"
#include "glog/logging.h"
#include "glm/gtx/string_cast.hpp"

using namespace std;
using namespace google;

Plane::Plane(weak_ptr<Scene> scene, const glm::vec3& size, const glm::vec3& center) :
BaseObject(ObjectType::PLANE, scene),
size_(size),
center_(center)
{
    model_ = glm::mat4(1.0f);
    model_ = glm::translate(model_, center_);
    model_ = glm::scale(model_, size_);
    LOG(WARNING) << "Plane construct, scale size :" << glm::to_string(size_) << ", center : " << glm::to_string(center_) << ", model matrix :"
    << glm::to_string(model_);
}

void Plane::Draw() {
    LOG_AT_LEVEL(INFO) << "Draw() begin";
    if (!glIsVertexArray(VAO_)) {
        ConstructGeometry();
    }

    LOG_AT_LEVEL(INFO) << "Draw() end";
}

void Plane::Update(float dt) {
    LOG_AT_LEVEL(INFO) << "Update begin, dt :" << dt;


    LOG_AT_LEVEL(INFO) << "Update end";
}

Plane::~Plane() {
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
}

void Plane::DrawShadow() {
    LOG_AT_LEVEL(INFO) << "DrawShadow() begin";
    if (!glIsVertexArray(VAO_)) {
        ConstructGeometry();
    }

    LOG_AT_LEVEL(INFO) << "DrawShaow() end";
}

void Plane::ConstructGeometry() {
    LOG_AT_LEVEL(INFO) << "ConstructGeometry() begin";
    // generate VAO_
    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);
    // generate VBO_
    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
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

    LOG_AT_LEVEL(INFO) << "ConstructGeometry() end, VAO_ :" << VAO_ << " VBO :" << VBO_;
}


