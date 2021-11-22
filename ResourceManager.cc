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


std::map<std::string, shared_ptr<Texture2D>>    ResourceManager::Textures;
std::map<std::string, shared_ptr<Shader>>       ResourceManager::Shaders;

shared_ptr<Shader> ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
    string name = string(vShaderFile) + "_" + string(fShaderFile);
    if (Shaders.count(name) == 0) {
        Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    }
    return Shaders[name];
}

shared_ptr<Texture2D> ResourceManager::LoadTexture(const GLchar *file)
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
    Shaders.clear();
    // (Properly) delete all textures
    Textures.clear();
}

shared_ptr<Shader> ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
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
        LOG(INFO) << "ERROR::SHADER: Failed to read Shader files";
    }
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    const GLchar *gShaderCode = geometryCode.c_str();
    // 创建shader
    shared_ptr<Shader> shader = make_shared<Shader>();
    shader->Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

shared_ptr<Texture2D> ResourceManager::loadTextureFromFile(const GLchar *file)
{
    // Create Texture object
    shared_ptr<Texture2D> texture = make_shared<Texture2D>();

    // Load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    if (nrChannels == 4)
    {
        texture->Internal_Format = GL_RGBA;
        texture->Image_Format = GL_RGBA;
    }
    // Now generate texture
    texture->Generate(width, height, data);
    // And finally free image data
    stbi_image_free(data);
    return texture;
}
