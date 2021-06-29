//
// Created by virgil on 2021/6/10.
//

#include "ResourceManager.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#include "third/stb_image.h"

#include "Log/LogUtil.h"
using namespace std;

std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;
std::mutex                          ResourceManager::mu_;

Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
{
    unique_lock<mutex> lc(mu_);
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    unique_lock<mutex> lc(mu_);
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const string &file, std::string name)
{
    unique_lock<mutex> lc(mu_);
    Textures[name] = loadTextureFromFile(file.c_str());
    return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    unique_lock<mutex> lc(mu_);
    return Textures[name];
}

void ResourceManager::Clear()
{
    // (Properly) delete all shaders
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // (Properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
    // 从文件读取对应的code
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        logE("ERROR::SHADER: Failed to read shader files\n");
    }
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    const GLchar *gShaderCode = geometryCode.c_str();
    // 创建shader
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const GLchar *file)
{
    // Create Texture object
    Texture2D texture;

    // Load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    if (!data) {
        logE("the %s file is not found", file);
    }
    if (nrChannels == 4)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    // Now generate texture
    texture.Generate(width, height, data);
    // And finally free image data
    stbi_image_free(data);
    return texture;
}
