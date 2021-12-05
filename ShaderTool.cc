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
    if (!object) return false;
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

bool ShaderTool::bindSimplePhongShader(std::shared_ptr<BaseObject> object) {
    if (!object) return false;
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

bool ShaderTool::bindShadowPhongShader(std::shared_ptr<BaseObject> object) {
    if (!object) return false;
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
    shadow_map->bind(0);
    auto light_view = light->getViewMatrix();
    auto light_projection = light->getProjectionMatrix();
    auto lightMVP = light_projection * light_view * object->getModelMatrix();
    shader->setMatrix4("lightMVP", lightMVP);
    return true;
}

bool ShaderTool::bindSimpleShadowShader(std::shared_ptr<BaseObject> object, const glm::mat4& view, const glm::mat4& projection) {
    if (!object) return false;
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

bool
ShaderTool::bindGbufferShader(std::shared_ptr<BaseObject> object, const glm::mat4 &view, const glm::mat4 &projection) {
    if (!object) return false;
    auto scene = object->getScene();
    if (!scene) return false;
    auto resource_manager  =scene->getResourceManager();
    auto shader = resource_manager->LoadShader("gBuffer.vs", "gBuffer.fs");
    shader->use();
    shader->setMatrix4("model", object->getModelMatrix());
    shader->setMatrix4("view", view);
    shader->setMatrix4("projection", projection);
    shader->setVector4f("albedoColor", object->getColor());
    shader->setFloat("farPlane", scene->getCamera()->getFar());
    shader->setFloat("nearPlane", scene->getCamera()->getNear());
    shader->setFloat("specularIntensity", 32.0f);
    return true;
}

bool ShaderTool::bindAOShader(std::shared_ptr<Scene> scene) {
    if (!scene) return false;
    auto resource_manager  =scene->getResourceManager();
    auto shader = resource_manager->LoadShader("ssao.vs", "ssao.fs");
    shader->use();
    shader->setMatrix4("projection", scene->getCamera()->getProjectionMatrix());
    shader->setFloat("screenWidth", scene->getWidth());
    shader->setFloat("screenHeight", scene->getHeight());
    shader->setInteger("fPosition", 0);
    shader->setInteger("fNormal", 1);
    shader->setInteger("fNoise", 2);
    scene->getAoPositionMap()->bind(0);
    scene->getAoNormalMap()->bind(1);
    scene->getSsaoNoiseMap()->bind(2);
    const auto& kernel = scene->getSsaoKernel();
    for (int i = 0; i < kernel.size(); ++i) {
        string str = "samples[" + to_string(i) + "]";
        shader->setVector3f(str.c_str(), kernel.at(i));
    }
    return true;
}

bool
ShaderTool::bindDebugShader(std::shared_ptr<BaseObject> object, std::shared_ptr<Texture2D> texture, DebugType type) {
    auto scene = object->getScene();
    if (!scene || !texture) {
        LOG(ERROR) << "scene ptr is nullptr";
        return false;
    }

    auto light = scene->getLight();
    auto resource_manager = scene->getResourceManager();
    auto shader = resource_manager->LoadShader("debugTexture.vs", "debugTexture.fs");
    shader->use();
    shader->setInteger("texUnit", 0);
    shader->setFloat("farPlane", light->getFarPlane());
    shader->setFloat("nearPlane", light->getNearPlane());
    shader->setInteger("type", static_cast<int>(type));
    texture->bind(0);
    return true;
}
