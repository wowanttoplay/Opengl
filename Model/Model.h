//
// Created by virgil on 2021/7/12.
//

#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>
#include <memory>

#include "Mesh.h"
#include "../Texture2D.h"

class Model {
public:
    explicit Model(const std::string& model_path);
    void Draw(Shader shader);
private:
    std::vector<Mesh> meshes_;
    std::string path_;

    void LoadModel(const std::string& model_path);
    void ProcessNode(aiNode *node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<std::shared_ptr<Texture2D>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& type_name);

    void LoadMeshVertices(const aiMesh *mesh, std::vector<Vertex> &vertices) const;

    void LoadMeshIndices(const aiMesh *mesh, std::vector<uint32_t> &indices) const;

    void LoadMeshTextures(const aiMesh *mesh, const aiScene *scene, std::vector<std::shared_ptr<Texture2D>> &textures);
};

