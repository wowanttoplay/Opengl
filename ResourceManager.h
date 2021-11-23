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

    /**
     * 传入工作目录,构造资源管理器
     * @param dir
     */
    explicit ResourceManager(const std::string& dir);

    virtual ~ResourceManager();

    std::shared_ptr<Shader> LoadShader(const std::string &vShaderFile, const std::string &fShaderFile, const std::string &gShaderFile = "");

    std::shared_ptr<Texture2D> LoadTexture(const std::string &file);

    // 设置工作目录
    void SetDir(const std::string& dir);


private:
    std::shared_ptr<Shader> loadShaderFromFile(const std::string &vShaderFile, const std::string &fShaderFile, const std::string &gShaderFile = nullptr);

    std::shared_ptr<Texture2D> loadTextureFromFile(const std::string &file);

    std::map<std::string, std::shared_ptr<Shader>>    Shaders;

    std::map<std::string, std::shared_ptr<Texture2D>> Textures;

    std::string shader_dir_; // shade 存放目录
    std::string texture_dir_; // 纹理存放目录
    std::string model_dir_; // 模型存放目录
};



