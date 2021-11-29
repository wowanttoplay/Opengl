//
// Created by virgil on 2021/6/10.
//

#pragma once
#include <glew.h>

class Texture2D
{
public:
    Texture2D(GLuint internalFormat = GL_RGB, GLuint imageFormate = GL_RGB, GLuint wrap_s = GL_REPEAT, GLuint wrap_t = GL_REPEAT, GLuint filter_min = GL_LINEAR, GLuint filter_max = GL_LINEAR, GLuint type = GL_UNSIGNED_BYTE, bool mipmap = false);

    virtual ~Texture2D();

    void generate(GLuint width, GLuint height, unsigned char* data);

    void bind() const;

    void setInternalFormat(GLuint internalFormat);

    void setImageFormate(GLuint imageFormate);

    GLuint getId() const;

    GLuint getWidth() const;

    GLuint getHeight() const;

private:
    GLuint id_;
    GLuint width_, height_;
    GLuint internal_format_;

    // Format of texture object
    GLuint image_formate_; // Format of loaded image

    GLuint wrap_s_;
    GLuint wrap_t_;
    GLuint filter_min_;
    GLuint filter_max_;
    GLuint type_;
    bool mipmap_;
};

