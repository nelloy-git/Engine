#pragma once

#include <string>

#include "Draw/Loader/DataLoader.h"

#include "Draw/Model.h"
#include "Draw/Types.h"

namespace tinygltf {
    class Accessor;
    class Image;
    class Material;
    class Mesh;
    class Model;
    class Node;
    class Primitive;
    class Scene;
    class Texture;
}

namespace Graphics::Draw {

class LoaderGltf : public DataLoader {
public:
    LoaderGltf();
    virtual ~LoaderGltf();

    void load(std::shared_ptr<Model> dst,
              const std::string &path,
              const DataIniter &initer) override;

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
                                          const tinygltf::Model &model);

    std::shared_ptr<Mesh> _loadMesh(const tinygltf::Mesh &mesh,
                                    const tinygltf::Model &model);

    std::shared_ptr<Primitive> _loadPrimitive(const tinygltf::Primitive &prim,
                                              const tinygltf::Model &model);

    std::shared_ptr<Node> _loadNode(const tinygltf::Node &node,
                                    const tinygltf::Model &model);

    std::shared_ptr<Scene> _loadScene(const tinygltf::Scene &scene,
                                      const tinygltf::Model &model);

    void _linkNodes(const tinygltf::Model &model);

    template<typename T, typename V>
    using GetterType = T (LoaderGltf::*)(const V&, const tinygltf::Model&);

    template<typename T, typename V>
    std::vector<T> _iterate(const std::vector<V> &gltf_list,
                            const tinygltf::Model &model,
                            GetterType<T, V> getter){

        std::vector<T> list;

        for (int i = 0; i < gltf_list.size(); i++){
            auto &gltf_obj = gltf_list[i];
            int err_count = _errors.size();
            list.push_back((this->*getter)(gltf_obj, model));

            for (int j = err_count; j < _errors.size(); j++){
                _errors[j] = toString<V>() + "[" + std::to_string(j) + "]: " + _errors[j];
            }
        }

        return list;
    }

    
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