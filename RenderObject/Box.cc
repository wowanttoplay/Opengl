//
// Created by virgil on 2021/6/11.
//

#include "Box.h"
#include <glog/logging.h>
#include <glm/gtx/string_cast.hpp>
#include "../Data/vertex_data.h"
#include "../ResourceManager.h"
#include "../Scene.h"
#include "../ShaderTool.h"

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

void Box::drawDepthMap(const glm::mat4 &view, const glm::mat4 &projection) {
    if (!ShaderTool::bindSimpleShadowShader(shared_from_this(), view, projection)) {
        LOG(ERROR) << "bind simple shadow failed, return";
        return;
    }
    // draw vertex
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Box::draw() {
    auto scene = getScene();
    if (scene->isOpenShadow()) {
        drawShadowPhong();
    }else if (scene->isOpenAo()) {

    }else {
        drawSimplePhong();
    }
}

void Box::drawShadowPhong() {
    if (!glIsVertexArray(VAO_)) {
        constructGeometry();
    }

    if (!ShaderTool::bindShadowPhongShader(shared_from_this())) {
        LOG(ERROR) << "bind shadow phong failed, return";
        return;
    }
    // draw vertex
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Box::drawSimplePhong() {
    if (!glIsVertexArray(VAO_)) {
        constructGeometry();
    }

    if (!ShaderTool::bindSimplePhongShader(shared_from_this())) {
        LOG(ERROR) << "bind saimple phong failed, retunr";
        return;
    }
    // draw vertex
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Box::simpleColorDraw() {
    if (!glIsVertexArray(VAO_)) {
        constructGeometry();
    }

    if (!ShaderTool::bindSimpleColorShader(shared_from_this())) {
        LOG(ERROR) << "bind simple color shader failed, return";
        return;
    }
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

void Box::drawGBuffer(const glm::mat4& view, const glm::mat4& projection) {
    if (!glIsVertexArray(VAO_)) {
        constructGeometry();
    }

    if (!ShaderTool::bindGbufferShader(shared_from_this(), view, projection)) {
        LOG(ERROR) << "bind g buffer failed, return";
        return;
    }

    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
