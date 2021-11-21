//
// Created by virgil on 2021/6/10.
//

#include "ResourceManager.h"
#include <sstream>
#include <iostream>
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include "third/stb_image.h"
#include "glog/logging.h"

using namespace std;


std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
    string name = string(vShaderFile) + "_" + string(fShaderFile);
    if (Shaders.count(name) == 0) {
        Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    }
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const GLchar *file)
{
    string name(file);
    if (Textures.count(name) == 0) {
        Textures[name] = loadTextureFromFile(file);
    }
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
        LOG(INFO) << "ERROR::SHADER: Failed to read shader files";
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
