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
#include "../Shader.h"
#include "../Texture2D.h"

using namespace std;
using namespace google;

Plane::Plane(shared_ptr<Scene> scene, const glm::vec3& scale, const glm::vec3& position) :
        BaseObject(ObjectType::Plane, scene, scale, position)
{
    LOG(WARNING) << "Plane(), ptr : " << this;
}

void Plane::draw() {
    SimpleColorDraw();

}

void Plane::SimpleColorDraw() {
    if (!glIsVertexArray(VAO_)) {
        ConstructGeometry();
    }
    auto scene = getScene();
    if (!scene) {
        LOG(ERROR) << "scene ptr is nullptr";
        return;
    }
    auto camera = scene->getCamera();
    auto resource_manager = scene->getResourceManager();
    const glm::mat4 view = camera->getViewMatrix();
    const glm::mat4 projective = camera->getProjectionMatrix();
    auto MVP = projective * view * getModelMatrix();
    auto shader = resource_manager->LoadShader("color.vs", "color.fs");

    shader->use();
    shader->setMatrix4("MVP", MVP);
    shader->setVector4f("objectColor", getColor());

    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Plane::update() {

}

Plane::~Plane() {
    LOG(WARNING) << "~Plane(), ptr : " << this;
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
}

void Plane::drawShadow() {
    if (!glIsVertexArray(VAO_)) {
        ConstructGeometry();
    }

}

void Plane::ConstructGeometry() {
    LOG_AT_LEVEL(WARNING) << "constructGeometry() begin";
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

    LOG_AT_LEVEL(WARNING) << "constructGeometry() end, VAO_ :" << VAO_ << " VBO_ :" << VBO_;
}


