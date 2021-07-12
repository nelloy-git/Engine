#pragma once

#include <string>

#include "Draw/Loader/DataLoader.h"

#include "Draw/Model.h"
#include "Draw/Types.h"

namespace tinygltf {
    class Accessor;
    class Material;
    class Mesh;
    class Model;
    class Node;
    class Primitive;
    class Texture;
    class Image;
}

namespace Graphics::Draw {

class LoaderGltf : public DataLoader {
public:
    LoaderGltf();
    virtual ~LoaderGltf();

    void load(std::shared_ptr<Model> dst,
              const std::string &path,
              const DataIniter &initer) override;
    void load(std::shared_ptr<Model> dst,
              const std::string &path,
              const DataIniter &initer) const override;

private:
    std::shared_ptr<Model> _result;
    DataIniter const *_initer;
    std::vector<std::string> _errors;

    tinygltf::Model *_loadGltfModel(const std::string &path);

    std::shared_ptr<Buffer> _loadBuffer(const tinygltf::Accessor &accessor,
                                        const tinygltf::Model &model);

    std::shared_ptr<Material> _loadMaterial(const tinygltf::Material &material,
                                            const tinygltf::Model &model);

    std::shared_ptr<Texture> _loadTexture(const tinygltf::Texture &texture,
                                          const tinygltf::Model &Model);

    std::shared_ptr<Mesh> _loadMesh(const tinygltf::Mesh &mesh,
                                    const tinygltf::Model &model);

    std::shared_ptr<Primitive> _loadPrimitive(const tinygltf::Primitive prim,
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