//
// Created by virgil on 2021/6/10.
//

#pragma once
#include <map>
#include <string>
#include <glew.h>
#include "Shader.h"
#include "Texture2D.h"
#include "memory.h"


class ResourceManager
{
public:

    static std::map<std::string, std::shared_ptr<Shader>>    Shaders;
    static std::map<std::string, std::shared_ptr<Texture2D>> Textures;

    static std::shared_ptr<Shader> LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile);

    static std::shared_ptr<Texture2D> LoadTexture(const GLchar *file);

    static void      Clear();
private:

    ResourceManager() = default;

    static std::shared_ptr<Shader> loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);

    static std::shared_ptr<Texture2D> loadTextureFromFile(const GLchar *file);
};



