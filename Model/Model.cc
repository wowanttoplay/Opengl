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

void Model::Render(Shader shader, glm::mat4 view, glm::mat4 projection) {
    shader.Use();
    shader.SetMatrix4("view", view);
    shader.SetMatrix4("projection", projection);
    glm::mat4 model = glm::mat4(1.0);
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
    model = glm::scale(model, glm::vec3(1.0));
    shader.SetMatrix4("model", model);
    for (int i = 0; i < meshes_.size(); ++i) {
        meshes_.at(i).Render(shader);
    }
}

void Model::LoadModel(const std::string &model_path) {
    logI("load model : %s", model_path.c_str());
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(model_path,
                                           aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        logE("ASSIMP::%s", import.GetErrorString());
        return;
    }
    path_ = model_path;
    directory_ = path_.substr(0, path_.rfind("/") + 1);
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
    map<string, shared_ptr<Texture2D>> textures;

    // init vertices
    LoadMeshVertices(mesh, vertices);

    // init indices
    LoadMeshIndices(mesh, indices);

    // init materials
    LoadMeshTextures(mesh, scene, textures);

    return Mesh(vertices, indices, textures);
}

void Model::LoadMeshTextures(const aiMesh *mesh, const aiScene *scene, map<string, shared_ptr<Texture2D>> &textures) {

    if (!ResourceManager::GetTexture(directory_ + "albedo")) {
        ResourceManager::LoadTexture(directory_ + "albeto.png", directory_ + "albeto");
    }
    if (!ResourceManager::GetTexture(directory_ + "metallic")) {
        ResourceManager::LoadTexture(directory_ + "metallic.png", directory_ + "metallic");
    }
    if (!ResourceManager::GetTexture(directory_ + "normal")) {
        ResourceManager::LoadTexture(directory_ + "normal.png", directory_ + "normal");
    }
    if (!ResourceManager::GetTexture(directory_ + "roughness")) {
        ResourceManager::LoadTexture(directory_ + "roughness.png", directory_ + "roughness");
    }
    if (!ResourceManager::GetTexture(directory_ + "ao")) {
        ResourceManager::LoadTexture(directory_ + "ao.png", directory_ + "ao");
    }
    textures["albeto"] = ResourceManager::GetTexture(directory_ + "albeto");
    textures["metallic"] = ResourceManager::GetTexture(directory_ + "metallic");
    textures["normal"] = ResourceManager::GetTexture(directory_ + "normal");
    textures["roughness"] = ResourceManager::GetTexture(directory_ + "roughness");
    textures["ao"] = ResourceManager::GetTexture(directory_ + "ao");

//    if (mesh->mMaterialIndex >= 0) {
//        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
////        aiString base_color, roughness, metallic, normal, ao;
////        material->GetTexture(aiTextureType_DIFFUSE, 1, &base_color);
////        material->GetTexture(aiTextureType_SPECULAR, 1, &roughness);
////        material->GetTexture(aiTextureType_UNKNOWN, 1, &metallic);
////        material->GetTexture(aiTextureType_NORMALS, 0, &normal);
////        material->GetTexture(aiTextureType_AMBIENT, 1, &ao);
//
//        vector<shared_ptr<Texture2D>> albedo = LoadMaterialTextures(material, aiTextureType_DIFFUSE,
//                                                                    "albedo");
//        textures.insert(textures.end(), albedo.begin(), albedo.end());
//        vector<shared_ptr<Texture2D>> roughness = LoadMaterialTextures(material, aiTextureType_SPECULAR,
//                                                                       "roughness");
//        textures.insert(textures.end(), roughness.begin(), roughness.end());
//        vector<shared_ptr<Texture2D>> normal = LoadMaterialTextures(material, aiTextureType_NORMALS, "normal");
//        textures.insert(textures.end(), normal.begin(), normal.end());
//        vector<shared_ptr<Texture2D>> metal = LoadMaterialTextures(material, aiTextureType_UNKNOWN, "metallic");
//        textures.insert(textures.end(), metal.begin(), metal.end());
//        vector<shared_ptr<Texture2D>> ao = LoadMaterialTextures(material, aiTextureType_AMBIENT, "ao");
//        textures.insert(textures.end(), ao.begin(), ao.end());
//
//    }
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
        if (mesh->mNormals) {
            position.x = mesh->mNormals[i].x;
            position.y = mesh->mNormals[i].y;
            position.z = mesh->mNormals[i].z;
        }
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
        logI("%s find texture type :%s", path_.c_str(), type_name.c_str());
        aiString file_path;
        mat->GetTexture(type, i, &file_path);
        string real_path = path_;
        real_path = real_path.substr(0, real_path.rfind('/') + 1);
        real_path += file_path.C_Str();

        if (ResourceManager::GetTexture(real_path)) {
            textures.push_back(ResourceManager::GetTexture(real_path));
        } else {
            shared_ptr<Texture2D> texture = ResourceManager::LoadTexture(real_path, real_path);
            if (texture) {
                textures.push_back(texture);
            }
        }
        textures.back()->name = type_name;
    }
    return textures;
}
