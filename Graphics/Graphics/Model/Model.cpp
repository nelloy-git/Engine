#include "Graphics/Model/Model.hpp"

#include "tiny_gltf.h"

using namespace Graphics::Model;

// ModelBase::ModelBase(const tinygltf::Model &gltf_model){
//     // _loadTextures(gltf_model);
//     // Textures must be loaded before materials
//     // _loadMaterials(gltf_model);
// }

// Material *ModelBase::getMaterial(int n) const {
//     return _getPtr(materials, n);
// }

// Texture *ModelBase::getTexture(int n) const {
//     return _getPtr(textures, n);
// }

// void ModelBase::_loadTextures(const tinygltf::Model &model){
//     for (int i = 0; i < model.textures.size(); ++i){
//         auto tex = new Texture(this, i, model, model.textures[i]);
//         textures.emplace_back(tex);
//     }
// }

// void ModelBase::_loadMaterials(const tinygltf::Model &model){
//     for (int i = 0; i < model.materials.size(); ++i){
//         auto material = new Material(this, i, model, model.materials[i]);
//         materials.emplace_back(material);
//     }
// }

// tinygltf::Model *Model::_loadGltfModel(const std::string &path) const {
//     tinygltf::TinyGLTF loader;
//     std::string err;
//     std::string warn;

//     auto gltf_model = new tinygltf::Model();

//     bool res = loader.LoadASCIIFromFile(gltf_model, &err, &warn, path);
//     if (!warn.empty()){
//         throw std::runtime_error(warn);
//     }

//     if (!err.empty()) {
//         throw std::runtime_error(err);
//     }

//     if (!res){
//         throw std::runtime_error("Failed to load glTF: " + path);
//     }

//     return gltf_model;
// }

// void Model::_loadMeshes(const tinygltf::Model &model){
//     for (int i = 0; i < model.meshes.size(); ++i){
//         auto mesh = new Mesh(this, i, model, model.meshes[i]);
//         meshes.emplace_back(mesh);
//     }
// }