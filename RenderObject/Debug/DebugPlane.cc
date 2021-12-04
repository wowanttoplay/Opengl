//
// Created by virgil on 2021/11/29.
//

#include "DebugPlane.h"
#include <glm/glm.hpp>
#include <glog/logging.h>
#include "../../Data/vertex_data.h"
#include "../../Scene.h"

using namespace std;
using namespace google;

DebugPlane::~DebugPlane() {
    LOG(WARNING) << "~DebugPlane(), ptr : " << this;
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
}

DebugPlane::DebugPlane(std::shared_ptr<Scene> scene)
: BaseObject(ObjectType::DeubgPlane, scene, glm::vec3(1.0), glm::vec3(1.0))
{
    LOG(WARNING) << "DebugPlane(), ptr : " << this;
}

void DebugPlane::drawTexture(std::shared_ptr<Texture2D> texture, DebugType type) {
    if (!glIsVertexArray(VAO_)) {
        constructGeometry();
    }
    auto scene = getScene();
    if (!scene) {
        LOG(ERROR) << "scene ptr is nullptr";
        return;
    }

    auto light = scene->getLight();
    auto resource_manager = scene->getResourceManager();
    auto shader = resource_manager->LoadShader("debugTexture.vs", "debugTexture.fs");
    shader->use();
    shader->setInteger("texUnit", 0);
    shader->setFloat("farPlane", light->getFarPlane());
    shader->setFloat("nearPlane", light->getNearPlane());
    shader->setInteger("type", static_cast<int>(type));
    texture->bind();
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void DebugPlane::constructGeometry() {
    LOG_AT_LEVEL(WARNING) << "constructGeometry() begin";
    // generate VAO_
    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);
    // generate VBO_
    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(RenderData::DebugVertcies), RenderData::DebugVertcies, GL_STATIC_DRAW);
    // attrib pointer
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    // unload
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    LOG_AT_LEVEL(WARNING) << "constructGeometry() end, VAO_ :" << VAO_ << " VBO_ :" << VBO_;
}

void DebugPlane::draw() {

}

void DebugPlane::update() {

}




