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
    model = glm::scale(model, glm::vec3(0.1));
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
    map<string, shared_ptr<Material>> metarials;

    // init vertices
    LoadMeshVertices(mesh, vertices);

    // init indices
    LoadMeshIndices(mesh, indices);

    // init materials
    LoadMeshTextures(mesh, scene, metarials);

    return Mesh(vertices, indices, metarials);
}

void Model::LoadMeshTextures(const aiMesh *mesh, const aiScene *scene, map<string, shared_ptr<Material>> &materials) {
    // load texture
    if (mesh->mMaterialIndex < 0) {
        return;
    }
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    materials["albedo"] = make_shared<Material>();
    materials["roughness"] = make_shared<Material>();
    materials["ao"] = make_shared<Material>();
    materials["normal"] = make_shared<Material>();
    materials["metallic"] = make_shared<Material>();
    // paramter
    material->Get(AI_MATKEY_COLOR_DIFFUSE, materials["albedo"]->data);
    materials["roughness"]->data = glm::vec3(0.0);
    materials["ao"]->data = glm::vec3(1.0);
//    material->Get(AI_MATKEY_COLOR_SPECULAR, materials["roughness"]->data);
//    material->Get(AI_MATKEY_COLOR_AMBIENT, materials["ao"]->data);
    materials["normal"]->data = glm::vec3(0.0); // 无效值，只是为了统一
    materials["metallic"]->data = glm::vec3(0.0); // 默认不是金属

    // texture
    vector<shared_ptr<Texture2D>> albedo = LoadMaterialTextures(material, aiTextureType_DIFFUSE,
                                                                "albedo");
    vector<shared_ptr<Texture2D>> roughness = LoadMaterialTextures(material, aiTextureType_SPECULAR,
                                                                   "roughness");
    vector<shared_ptr<Texture2D>> normal = LoadMaterialTextures(material, aiTextureType_NORMALS, "normal");
    vector<shared_ptr<Texture2D>> metallic = LoadMaterialTextures(material, aiTextureType_UNKNOWN, "metallic");
    vector<shared_ptr<Texture2D>> ao = LoadMaterialTextures(material, aiTextureType_AMBIENT, "ao");
    if (!albedo.empty()) {
        materials["albedo"]->texture = albedo.front();
    }
    if (!roughness.empty()) {
        materials["roughness"]->texture = roughness.front();
    }
    if (!normal.empty()) {
        materials["normal"]->texture = normal.front();
    }
    if (!metallic.empty()) {
        materials["metallic"]->texture = metallic.front();
    }
    if (!ao.empty()) {
        materials["ao"]->texture = ao.front();
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


//    for (int i = 0; i < mat->GetTextureCount(type); ++i) {
        logI("%s find texture type :%s", path_.c_str(), type_name.c_str());
        aiString file_path;
        mat->GetTexture(type, 0, &file_path);
        string real_path = path_;
        real_path = real_path.substr(0, real_path.rfind('/') + 1);
//        real_path += file_path.C_Str();
        if (type == aiTextureType_DIFFUSE) {
            real_path += "Textures/Cerberus_A.tga";
        }else if (type == aiTextureType_SPECULAR) {
            real_path += "Textures/Cerberus_R.tga";
        }else if (type == aiTextureType_NORMALS) {
            real_path += "Textures/Cerberus_N.tga";
        }else if (type == aiTextureType_UNKNOWN) {
            real_path += "Textures/Cerberus_M.tga";
        }else if (type == aiTextureType_AMBIENT) {
//            real_path += "AO.tif";
            return vector<shared_ptr<Texture2D>>();
        }
        if (real_path.rfind("\\") != real_path.npos) {
            real_path = real_path.replace(real_path.rfind("\\"), 1, "/");
        }

        if (ResourceManager::GetTexture(real_path)) {
            textures.push_back(ResourceManager::GetTexture(real_path));
        } else {
            shared_ptr<Texture2D> texture = ResourceManager::LoadTexture(real_path, real_path);
            if (texture) {
                textures.push_back(texture);
            }
        }
        textures.back()->name = type_name;
//    }
    return textures;
}
