//
// Created by virgil on 2021/6/10.
//

#pragma once
#include <glew.h>
#include <string>

class Texture2D
{
public:

    GLuint ID;

    GLuint Width, Height;
    GLuint Internal_Format; // Format of texture object
    GLuint Image_Format; // Format of loaded image

    GLuint Wrap_S;
    GLuint Wrap_T;
    GLuint Filter_Min;
    GLuint Filter_Max;
    std::string name; // 纹理名称,方便辨别这是个什么纹理


    bool ready_ = false;

    Texture2D();

    void Generate(GLuint width, GLuint height, unsigned char* data);
    void Generate(GLuint width, GLuint height, float* data);

    void Bind() const;
};

