//
// Created by virgil on 2021/6/10.
//

#include "Plane.h"

#include <utility>
#include "../Data/vertex_data.h"
#include "../ResourceManager.h"
#include "glog/logging.h"
#include "glm/gtx/string_cast.hpp"
#include "../Scene.h"

using namespace std;
using namespace google;

Plane::Plane(shared_ptr<Scene> scene, const glm::vec3& scale, const glm::vec3& center) :
        BaseObject(ObjectType::PLANE, scene),
        scale_(scale),
        center_(center)
{
    model_ = glm::mat4(1.0f);
    model_ = glm::translate(model_, center_);
    model_ = glm::scale(model_, scale_);
    LOG(WARNING) << "Plane construct, scale scale :" << glm::to_string(scale_) << ", center : " << glm::to_string(center_) << ", model matrix :"
                 << glm::to_string(model_);
}

void Plane::Draw() {
    if (!glIsVertexArray(VAO_)) {
        ConstructGeometry();
    }
    auto scene = GetScene();
    if (!scene) LOG(ERROR) << "scene ptr is nullptr";
    auto camera = scene->GetCamera();
    auto resource_manager = scene->GetResourceManager();
    const glm::mat4 view = camera->GetViewMatrix();
    const glm::mat4 projective = camera->GetProjectionMatrix();
    auto MVP = projective * view * model_;
    auto shader = resource_manager->LoadShader("color.vs", "color.fs");

    shader->Use();
    shader->SetMatrix4("MVP", MVP);
    shader->SetVector3f("objectColor", glm::vec3(1.0f, 0.5f, 0.0f));

    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Plane::Update(float dt) {
    LOG_AT_LEVEL(INFO) << "Update begin, dt :" << dt;
    LOG_AT_LEVEL(INFO) << "Update end";
}

Plane::~Plane() {
    LOG(WARNING) << "~Plane(), ptr : " << this;
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
    LOG_AT_LEVEL(WARNING) << "ConstructGeometry() begin";
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

    LOG_AT_LEVEL(WARNING) << "ConstructGeometry() end, VAO_ :" << VAO_ << " VBO :" << VBO_;
}


