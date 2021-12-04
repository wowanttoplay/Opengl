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
#include "../ShaderTool.h"

using namespace std;
using namespace google;

Plane::Plane(shared_ptr<Scene> scene, const glm::vec3& scale, const glm::vec3& position) :
        BaseObject(ObjectType::Plane, scene, scale, position)
{
    LOG(WARNING) << "Plane(), ptr : " << this;
}

void Plane::draw() {
    if (!glIsVertexArray(VAO_)) {
        constructGeometry();
    }
    auto scene = getScene();
    if (scene->isOpenShadow()) {
        drawShadowPhong();
    }else if (scene->isOpenAo()) {

    }else{
        drawSimplePhong();
    }
}

void Plane::drawShadowPhong() {
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
    auto shader = resource_manager->LoadShader("phongShadow.vs", "phongShadow.fs");
    shader->use();
    shader->setMatrix4("model", getModelMatrix());
    shader->setMatrix4("view", view);
    shader->setMatrix4("projection", projection);
    shader->setVector4f("objectColor", getColor());
    shader->setFloat("specularIntensity", 32.0f);
    shader->setVector3f("cameraPos", camera->getPosition());
    shader->setVector3f("light.position", light->getPosition());
    shader->setVector3f("light.color", light->getColor());
    shader->setFloat("light.radius", light->getScale().x);
    shader->setFloat("light.nearPlane", light->getNearPlane());
    shader->setFloat("light.farPlane", light->getFarPlane());
    // set shadow
    shared_ptr<Texture2D> shadow_map = scene->getShadowMap();
    shader->setInteger("shadowMap", 0);
    shadow_map->bind();
    auto light_view = light->getViewMatrix();
    auto light_projection = light->getProjectionMatrix();
    auto lightMVP = light_projection * light_view * getModelMatrix();
    shader->setMatrix4("lightMVP", lightMVP);

    // draw vertex
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Plane::drawSimplePhong() {
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
    shader->setFloat("specularIntensity", 8.0f);
    shader->setVector3f("cameraPos", camera->getPosition());
    shader->setVector3f("light.position", light->getPosition());
    shader->setVector3f("light.color", light->getColor());

    // draw vertex
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Plane::simpleColorDraw() {
    if (!glIsVertexArray(VAO_)) {
        constructGeometry();
    }
    if (!ShaderTool::bindSimpleColorShader(shared_from_this())){
        LOG(ERROR) << "bind simple color shader failed, return";
        return;
    }
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

void Plane::drawDepthMap(const glm::mat4 &view, const glm::mat4 &projection) {
    if (!glIsVertexArray(VAO_)) {
        constructGeometry();
    }
    auto scene = getScene();
    if (!scene) {
        LOG(ERROR) << "scene ptr is nullptr";
        return;
    }
    auto resource_manager = scene->getResourceManager();
    auto shader = resource_manager->LoadShader("simpleShadow.vs", "simpleShadow.fs");
    shader->use();
    shader->setMatrix4("model", getModelMatrix());
    shader->setMatrix4("view", view);
    shader->setMatrix4("projection", projection);
    // draw vertex
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Plane::constructGeometry() {
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

void Plane::drawTexture(std::shared_ptr<Texture2D> texture) {
    if (!glIsVertexArray(VAO_)) {
        constructGeometry();
    }
    auto scene = getScene();
    if (!scene) {
        LOG(ERROR) << "scene ptr is nullptr";
        return;
    }
    auto resource_manager = scene->getResourceManager();
    auto shader = resource_manager->LoadShader("texture.vs", "texture.fs");
    shader->use();
    shader->setInteger("texUnit", 0);
    texture->bind();
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Plane::drawGBuffer(const glm::mat4 &view, const glm::mat4 &projection) {

}


