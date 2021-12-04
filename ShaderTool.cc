//
// Created by virgil on 2021/12/4.
//

#include "ShaderTool.h"
#include <glog/logging.h>

#include "Scene.h"
#include "Shader.h"
#include "Texture2D.h"

using namespace std;
using namespace google;

bool ShaderTool::bindSimpleColorShader(std::shared_ptr<BaseObject> object) {
    auto scene = object->getScene();
    if (!scene) {
        LOG(ERROR) << "scene ptr is nullptr";
        return false;
    }
    // set shader
    auto camera = scene->getCamera();
    auto resource_manager = scene->getResourceManager();
    const glm::mat4 view = camera->getViewMatrix();
    const glm::mat4 projective = camera->getProjectionMatrix();
    auto MVP = projective * view * object->getModelMatrix();
    auto shader = resource_manager->LoadShader("color.vs", "color.fs");
    shader->use();
    shader->setMatrix4("MVP", MVP);
    shader->setVector4f("objectColor", object->getColor());
    return true;
}

bool ShaderTool::bindSimplePhong(std::shared_ptr<BaseObject> object) {
    auto scene = object->getScene();
    if (!scene) {
        LOG(ERROR) << "scene ptr is nullptr";
        return false;
    }
    // set shader
    auto camera = scene->getCamera();
    auto resource_manager = scene->getResourceManager();
    auto light = scene->getLight();
    const glm::mat4 view = camera->getViewMatrix();
    const glm::mat4 projection = camera->getProjectionMatrix();
    auto shader = resource_manager->LoadShader("phong.vs", "phong.fs");
    shader->use();
    shader->setMatrix4("model", object->getModelMatrix());
    shader->setMatrix4("view", view);
    shader->setMatrix4("projection", projection);

    shader->setVector4f("objectColor", object->getColor());
    shader->setFloat("specularIntensity", 32.0f);
    shader->setVector3f("cameraPos", camera->getPosition());
    shader->setVector3f("light.position", light->getPosition());
    shader->setVector3f("light.color", light->getColor());
    return true;
}

bool ShaderTool::bindShadowPhong(std::shared_ptr<BaseObject> object) {
    auto scene = object->getScene();
    if (!scene) {
        LOG(ERROR) << "scene ptr is nullptr";
        return false;
    }
    // set shader
    auto camera = scene->getCamera();
    auto resource_manager = scene->getResourceManager();
    auto light = scene->getLight();
    const glm::mat4 view = camera->getViewMatrix();
    const glm::mat4 projection = camera->getProjectionMatrix();
    auto shader = resource_manager->LoadShader("phongShadow.vs", "phongShadow.fs");
    shader->use();
    shader->setMatrix4("model", object->getModelMatrix());
    shader->setMatrix4("view", view);
    shader->setMatrix4("projection", projection);
    shader->setVector4f("objectColor", object->getColor());
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
    auto lightMVP = light_projection * light_view * object->getModelMatrix();
    shader->setMatrix4("lightMVP", lightMVP);
    return true;
}

bool ShaderTool::bindSimpleShadow(std::shared_ptr<BaseObject> object, const glm::mat4& view, const glm::mat4& projection) {
    auto scene = object->getScene();
    if (!scene) {
        LOG(ERROR) << "scene ptr is nullptr";
        return false;
    }
    auto resource_manager = scene->getResourceManager();
    auto shader = resource_manager->LoadShader("simpleShadow.vs", "simpleShadow.fs");
    shader->use();
    shader->setMatrix4("model", object->getModelMatrix());
    shader->setMatrix4("view", view);
    shader->setMatrix4("projection", projection);
    return true;
}
