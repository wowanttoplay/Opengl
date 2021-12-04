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
