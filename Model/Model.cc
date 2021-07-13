//
// Created by virgil on 2021/7/12.
//

#include "Model.h"
#include "../Log/LogUtil.h"
#include "../ResourceManager.h"

using namespace std;

Model::Model(const std::string &model_path) {
    logI("load model : %s", model_path.c_str());
    LoadModel(model_path);
}

void Model::Draw(Shader shader) {
    for (int i = 0; i < meshes_.size(); ++i) {
        meshes_.at(i).Render(shader);
    }
}

void Model::LoadModel(const std::string &model_path) {
    logI("load model : %s", model_path.c_str());
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(model_path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        logE("ASSIMP::%s", import.GetErrorString());
        return;
    }
    path_ = model_path;
    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode *node, const aiScene *scene) {
    // 处理该节点所有的网格
    for (int i = 0; i < node->mNumMeshes; ++i) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes_.push_back(ProcessMesh(mesh, scene));
    }
    // 递归处理它的子节点
    for (int i = 0; i < node->mNumChildren; ++i) {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
    vector<Vertex> vertices;
    vector<uint32_t> indices;
    vector<shared_ptr<Texture2D>> textures;

    // init vertices
    LoadMeshVertices(mesh, vertices);

    // init indices
    LoadMeshIndices(mesh, indices);

    // init materials
    LoadMeshTextures(mesh, scene, textures);

    return Mesh(vertices, indices, textures);
}

void Model::LoadMeshTextures(const aiMesh *mesh, const aiScene *scene, vector<shared_ptr<Texture2D>> &textures) {
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        vector<shared_ptr<Texture2D>> base_color = LoadMaterialTextures(material, aiTextureType_BASE_COLOR,
                                                                        "base_color");
        textures.insert(textures.end(), base_color.begin(), base_color.end());
        vector<shared_ptr<Texture2D>> roughness = LoadMaterialTextures(material, aiTextureType_DIFFUSE_ROUGHNESS,
                                                                       "roughness");
        textures.insert(textures.end(), roughness.begin(), roughness.end());
        vector<shared_ptr<Texture2D>> normal = LoadMaterialTextures(material, aiTextureType_NORMAL_CAMERA, "normal");
        textures.insert(textures.end(), normal.begin(), normal.end());
        vector<shared_ptr<Texture2D>> metal = LoadMaterialTextures(material, aiTextureType_METALNESS, "metal");
        textures.insert(textures.end(), metal.begin(), metal.end());
    }
}

void Model::LoadMeshIndices(const aiMesh *mesh, vector<uint32_t> &indices) const {
    for (int i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }
}

void Model::LoadMeshVertices(const aiMesh *mesh, vector<Vertex> &vertices) const {
    vertices.resize(mesh->mNumVertices);
    for (int i = 0; i < mesh->mNumVertices; ++i) {
        Vertex &vertex = vertices.at(i);
        // read position
        glm::vec3 position;
        position.x = mesh->mVertices[i].x;
        position.y = mesh->mVertices[i].y;
        position.z = mesh->mVertices[i].z;
        vertex.position = position;
        // read normal
        position.x = mesh->mNormals[i].x;
        position.y = mesh->mNormals[i].y;
        position.z = mesh->mNormals[i].z;
        vertex.normal = position;
        // read texture coords
        glm::vec2 vec(0.0);
        if (mesh->mTextureCoords[0]) {
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
        }
        vertex.texture_coords = vec;
    }
}

std::vector<std::shared_ptr<Texture2D>>
Model::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &type_name) {
    vector<shared_ptr<Texture2D>> textures;
    for (int i = 0; i < mat->GetTextureCount(type); ++i) {
        aiString file_path;
        mat->GetTexture(type, i, &file_path);

        if (ResourceManager::GetTexture(file_path.C_Str())) {
            textures.push_back(ResourceManager::GetTexture(file_path.C_Str()));
        } else {
            textures.push_back(ResourceManager::GetTexture(file_path.C_Str()));
        }
        textures.back()->name = type_name;
    }
    return textures;
}
