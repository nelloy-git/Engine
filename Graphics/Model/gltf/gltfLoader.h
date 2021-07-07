#pragma once

#include <string>

#include "Model/Model.h"

#include "Model/gltf/gltf.h"

namespace tinygltf {
    class Model;
    class Node;
    class Primitive;
}

namespace Graphics::Model {

class gltfLoader {
public:
    gltfLoader() = default;
    virtual ~gltfLoader() = default;

    std::shared_ptr<Model> load(const std::string &path);

private:
    tinygltf::Model *_loadGltfModel(const std::string &path);

    std::shared_ptr<Buffer> _loadBuffer(const tinygltf::Accessor &accessor,
                                        const tinygltf::Model &model);

    
    // std::shared_ptr<Node> _loadNode(const tinygltf::Node &gltf_node,
    //                                 const tinygltf::Model &gltf_model);                                    
    // std::shared_ptr<Mesh> _loadMesh(const tinygltf::Mesh &gltf_mesh,
    //                                 const tinygltf::Model &gltf_model);
    // std::shared_ptr<Primitive> _loadPrimitive(const tinygltf::Primitive &gltf_prim);
    // std::shared_ptr<Material> _loadMaterial(const tinygltf::Material &gltf_material);
    // std::shared_ptr<GLwrap::Tex2D> _loadTexture(const tinygltf::Texture &gltf_texture,
    //                                             const tinygltf::Model &model);
};

}