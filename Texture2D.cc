//
// Created by virgil on 2021/6/10.
//

#include "Texture2D.h"
#include <glog/logging.h>
#include <glm/glm.hpp>

using namespace std;
using namespace google;

Texture2D::Texture2D(GLuint internal_format, GLuint image_formate, GLuint wrap_s, GLuint wrap_t, GLuint filter_min, GLuint filter_max, GLuint type, bool mipmap)
        :width_(0),
         height_(0),
         internal_format_(internal_format),
         image_formate_(image_formate),
         wrap_s_(wrap_s),
         wrap_t_(wrap_t),
         filter_min_(filter_min),
         filter_max_(filter_max),
         type_(type),
         mipmap_(mipmap)
{
    glGenTextures(1, &this->id_);
    LOG(WARNING) << "Texture2D(), ptr : " << this << "\t id :" << id_;
}

void Texture2D::generate(GLuint width, GLuint height, unsigned char* data)
{
    this->width_ = width;
    this->height_ = height;
    // Create Texture
    glBindTexture(GL_TEXTURE_2D, this->id_);
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format_, width, height, 0, image_formate_, type_, data);
    if (mipmap_) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    // Set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_max_);
    if (wrap_s_ == GL_CLAMP_TO_BORDER || wrap_t_ == GL_CLAMP_TO_BORDER) {
        GLfloat borderColor[] = {1.0, 1.0, 1.0, 1.0};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind(int position) const
{
    glActiveTexture(GL_TEXTURE0 + position);
    glBindTexture(GL_TEXTURE_2D, this->id_);
}

Texture2D::~Texture2D() {
    LOG(WARNING) << "~Texture2D(), ptr : " << this << "\t , id : " << id_;
    glDeleteTextures(1, &this->id_);
}

void Texture2D::setInternalFormat(GLuint internalFormat) {
    internal_format_ = internalFormat;
}

void Texture2D::setImageFormate(GLuint imageFormate) {
    image_formate_ = imageFormate;
}

GLuint Texture2D::getId() const {
    return id_;
}

GLuint Texture2D::getWidth() const {
    return width_;
}

GLuint Texture2D::getHeight() const {
    return height_;
}

