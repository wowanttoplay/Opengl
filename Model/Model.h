//
// Created by virgil on 2021/7/12.
//

#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/pbrmaterial.h>
#include <vector>
#include <string>
#include <memory>
#include <map>

#include "Mesh.h"
#include "../Texture2D.h"

class Model {
public:
    explicit Model(const std::string& model_path);
    void Render(Shader shader, glm::mat4 view, glm::mat4 projection);
private:
    std::vector<Mesh> meshes_;
    std::string path_;
    std::string directory_;

    void LoadModel(const std::string& model_path);
    void ProcessNode(aiNode *node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<std::shared_ptr<Texture2D>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& type_name);

    void LoadMeshVertices(const aiMesh *mesh, std::vector<Vertex> &vertices) const;

    void LoadMeshIndices(const aiMesh *mesh, std::vector<uint32_t> &indices) const;

    void LoadMeshTextures(const aiMesh *mesh, const aiScene *scene, std::map<std::string, std::shared_ptr<Material>>& materials);
};

