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
using namespace google;



ResourceManager::ResourceManager(const string &dir) {
    shader_dir_ = dir + "shader/";
    texture_dir_ = dir + "texture/";
    model_dir_ = dir + "model/";
    LOG(ERROR) << "ResourceManager(), dir :" << dir;
    LOG(ERROR) << "shader dir :" << shader_dir_;
    LOG(ERROR) << "texture dir : " << texture_dir_;
    LOG(ERROR) << "model dir : " << model_dir_;
}

ResourceManager::~ResourceManager() {
    // (Properly) delete all shaders
    Shaders.clear();
    // (Properly) delete all textures
    Textures.clear();
    LOG(ERROR) << "~ResourceManager(), ptr : " << this;
}

shared_ptr<Shader> ResourceManager::LoadShader(const string &vShaderFile, const string &fShaderFile, const string &gShaderFile)
{
    CHECK(!vShaderFile.empty() && !fShaderFile.empty());
    string name = string(vShaderFile) + "_" + string(fShaderFile);
    string vFile = shader_dir_ + vShaderFile;
    string fFile = shader_dir_ + fShaderFile;
    string gFile = gShaderFile.empty() ? gShaderFile : shader_dir_ + gShaderFile;
    if (Shaders.count(name) == 0) {
        auto shader = loadShaderFromFile( vFile, fFile, gFile);
        CHECK(shader != nullptr);
        Shaders[name] = shader;
        LOG(WARNING) << "load shader, name :" << name << " ptr : " << shader.get();
    }
    return Shaders[name];
}

shared_ptr<Texture2D> ResourceManager::LoadTexture(const string &file)
{
    CHECK(!file.empty());
    string name(file);
    if (Textures.count(name) == 0) {
        auto texture = loadTextureFromFile(texture_dir_ + file);
        Textures[name] = texture;
        LOG(ERROR) << "load texture, name :" << name << "ptr :" << texture.get() << "width : " << texture->Width << " height : " << texture->Height;
    }
    return Textures[name];
}

shared_ptr<Shader> ResourceManager::loadShaderFromFile(const string &vShaderFile, const string &fShaderFile, const string &gShaderFile)
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

        if (!gShaderFile.empty() )
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
        LOG(ERROR) << "ERROR::SHADER: Failed to read Shader files";
    }
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    const GLchar *gShaderCode = geometryCode.empty() ? nullptr : geometryCode.c_str();
    // 创建shader
    shared_ptr<Shader> shader = make_shared<Shader>();
    shader->compile(vShaderCode, fShaderCode, gShaderCode);
    return shader;
}

shared_ptr<Texture2D> ResourceManager::loadTextureFromFile(const string &file)
{
    // Create Texture object
    shared_ptr<Texture2D> texture = make_shared<Texture2D>();

    // Load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);
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

void ResourceManager::SetDir(const string &dir) {

}


