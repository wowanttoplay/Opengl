//
// Created by virgil on 2021/6/11.
//

#include "Box.h"
#include <glog/logging.h>
#include <glm/gtx/string_cast.hpp>
#include "../Data/vertex_data.h"
#include "../ResourceManager.h"
#include "../Scene.h"

using namespace std;
using namespace google;

Box::Box(std::shared_ptr<Scene> scene, const glm::vec3 &scale, const glm::vec3 &position)
: BaseObject(ObjectType::Box, scene, scale, position)
{
    LOG(WARNING) << "Box(), ptr : " << this;
}

Box::~Box() {
    LOG(WARNING) << "~Box(), ptr : " << this;
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
}

void Box::drawShadow() {


}

void Box::draw() {
    if (!glIsVertexArray(VAO_)) {
        constructGeometry();
    }

    auto scene = getScene();
    if (!scene) {
        LOG(ERROR) << "scene ptr is nullptr";
        return;
    }
    // set shader
    auto camera = scene->getCamera();
    auto resource_manager = scene->getResourceManager();
    auto light = scene->getLight();
    const glm::mat4 view = camera->getViewMatrix();
    const glm::mat4 projection = camera->getProjectionMatrix();
    auto shader = resource_manager->LoadShader("phong.vs", "phong.fs");
    shader->use();
    shader->setMatrix4("model", getModelMatrix());
    shader->setMatrix4("view", view);
    shader->setMatrix4("projection", projection);

    shader->setVector4f("objectColor", getColor());
    shader->setFloat("specularIntensity", 32.0f);
    shader->setVector3f("cameraPos", camera->getPosition());
    shader->setVector3f("light.position", light->getPosition());
    shader->setVector3f("light.color", light->getColor());

    // draw vertex
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Box::simpleColorDraw() {
    if (!glIsVertexArray(VAO_)) {
        constructGeometry();
    }

    auto scene = getScene();
    if (!scene) {
        LOG(ERROR) << "scene ptr is nullptr";
        return;
    }
    // set shader
    auto camera = scene->getCamera();
    auto resource_manager = scene->getResourceManager();
    const glm::mat4 view = camera->getViewMatrix();
    const glm::mat4 projective = camera->getProjectionMatrix();
    auto MVP = projective * view * getModelMatrix();
    auto shader = resource_manager->LoadShader("color.vs", "color.fs");
    shader->use();
    shader->setMatrix4("MVP", MVP);
    shader->setVector4f("objectColor", getColor());
    // draw vertex
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Box::update() {

}

void Box::constructGeometry() {
    LOG_AT_LEVEL(WARNING) << "constructGeometry() begin";
    glGenVertexArrays(1, &this->VAO_);
    glBindVertexArray(this->VAO_);

    glGenBuffers(1, &this->VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_);
    glBufferData(GL_ARRAY_BUFFER,  sizeof(RenderData::boxVertices), RenderData::boxVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    LOG_AT_LEVEL(WARNING) << "constructGeometry() end, VAO_ :" << VAO_ << " VBO_ :" << VBO_;
}
