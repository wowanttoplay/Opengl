//
// Created by virgil on 2021/6/12.
//

#include "Sphere.h"
#include <glog/logging.h>
#include <glm/gtx/string_cast.hpp>
#include "../Texture2D.h"
#include "../Shader.h"
#include "../Scene.h"

using namespace std;
using namespace google;

Sphere::~Sphere() {
    LOG(WARNING) << "~Sphere(), ptr : " << this;
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
    glDeleteBuffers(1, &EBO_);
}

Sphere::Sphere(std::shared_ptr<Scene> scene, const glm::vec3 &scale, const glm::vec3 &position, int x_num, int y_num)
: BaseObject(ObjectType::Sphere, scene, scale, position),
x_num_(x_num),
y_num_(y_num)
{
    LOG(WARNING) << "Sphere(), ptr : " << this;
}

void Sphere::constructGeometry() {
    // 生成球面顶点数据
    float radius = 0.5f;
    for (int y = 0; y <= y_num_; y++) {
        for (int x = 0; x <= x_num_; x++) {
            float xSegment = (float) x / (float) x_num_;
            float ySegment = (float) y / (float) x_num_;
            float xPos = radius * std::cos(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);
            float yPos = radius * std::cos(ySegment * M_PI);
            float zPos = radius * std::sin(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);
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
    for (int i = 0; i < y_num_; i++) {
        for (int j = 0; j < x_num_; j++) {
            indices_data.push_back(i * (x_num_ + 1) + j);
            indices_data.push_back((i + 1) * (x_num_ + 1) + j);
            indices_data.push_back((i + 1) * (x_num_ + 1) + j + 1);
            indices_data.push_back(i * (x_num_ + 1) + j);
            indices_data.push_back((i + 1) * (x_num_ + 1) + j + 1);
            indices_data.push_back(i * (x_num_ + 1) + j + 1);
        }
    }

    // 绑定数据
    glGenVertexArrays(1, &this->VAO_);
    glBindVertexArray(this->VAO_);
    // VBO_
    glGenBuffers(1, &this->VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices_data.size() * sizeof(float), &vertices_data[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(GL_FLOAT)));
    // EBO_;
    glGenBuffers(1, &this->EBO_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_data.size() * sizeof(uint32_t), &indices_data[0], GL_STATIC_DRAW);
    //unload
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Sphere::drawDepthMap(const glm::mat4 &view, const glm::mat4 &projection) {
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

    glBindVertexArray(VAO_);
    glDrawElements(GL_TRIANGLES, indices_data.size(), GL_UNSIGNED_INT, 0);
}

void Sphere::draw() {
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
    glDrawElements(GL_TRIANGLES, indices_data.size(), GL_UNSIGNED_INT, 0);
}

void Sphere::drawSimpleColor() {
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
    glDrawElements(GL_TRIANGLES, indices_data.size(), GL_UNSIGNED_INT, 0);
}

void Sphere::update() {

}


