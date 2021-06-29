//
// Created by virgil on 2021/6/10.
//

#pragma once
#include <map>
#include <string>
#include <glew.h>
#include <mutex>

#include "Shader.h"
#include "Texture2D.h"


class ResourceManager
{
public:

    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D> Textures;


    static Shader   LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
    static Shader   GetShader(std::string name);

    static Texture2D LoadTexture(const std::string &file, std::string name);
    static Texture2D GetTexture(std::string name);

    static void      Clear();
private:
    static std::mutex mu_;
    ResourceManager() { }

    static Shader    loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);

    static Texture2D loadTextureFromFile(const GLchar *file);
};



