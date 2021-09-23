#pragma once

#include <memory>
#include <vector>

#include "Graphics/Render/Base/Material.hpp"
#include "Graphics/Render/Base/Vertex.hpp"

namespace Graphics::Model {

template<Render::Base::VertexStruct S>
class Mesh;

template<Render::Base::VertexStruct S>
class Node;

using Texture = Render::Base::Texture;

template<Render::Base::VertexStruct S>
class Model {
public:
    Model(){};
    Model(const Model &) = delete;
    Model(Model &&) = delete;
    Model(const Model &&) = delete;
    virtual ~Model() = default;

    std::vector<Mesh<S>> meshes;
    std::vector<Node<S>> nodes;
    std::vector<Texture> textures;

private:
};

}

// #include "Graphics/Model/Material.hpp"
// #include "Graphics/Model/Mesh.hpp"
// #include "Graphics/Model/Node.hpp"
// #include "Graphics/Model/Texture.hpp"

// namespace tinygltf {
//     class Accessor;
//     class Buffer;
//     class BufferView;
//     class Model;
//     class Primitive;
// }

    // glTF2.0 only
    // explicit Model(const tinygltf::Model &gltf_model) :
    //     ModelBase(gltf_model){
    //     _loadMeshes(gltf_model);
    // };

// class ModelBase {
// public:
//     // explicit ModelBase(const tinygltf::Model &gltf_model);
//     ModelBase() = default;
//     ModelBase(const ModelBase &) = delete;
//     virtual ~ModelBase() = 0;

//     // std::vector<Material> materials;
//     // std::vector<Texture> textures;

// protected:
//     // void _loadTextures(const tinygltf::Model &model);
//     // void _loadMaterials(const tinygltf::Model &model);

//     // template<class T>
//     // inline T *_getPtr(const std::vector<std::unique_ptr<T>> &list, int index) const {
//     //     if (index < 0 || index > list.size()){
//     //         return nullptr;
//     //     }
//     //     return list[index].get();
//     // }
// };


    // Mesh<S> *getMesh(int index) const {
    //     return _getPtr(meshes, index);
    // };

    // std::vector<std::unique_ptr<Animation>> animations;
    // std::vector<std::unique_ptr<Buffer>> buffers;
    // std::vector<std::unique_ptr<Node>> nodes;
    // std::vector<std::unique_ptr<Scene>> scenes;

// inline ModelBase::~ModelBase(){}
    // tinygltf::Model *_loadGltfModel(const std::string &path) const;
    
    // void _loadMeshes(const tinygltf::Model &model){
    //     for (int i = 0; i < model.meshes.size(); ++i){
    //         auto mesh = new Mesh(this, i, model, model.meshes[i]);
    //         meshes.emplace_back(mesh);
    // }
// };