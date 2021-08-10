#pragma once

#include <string>

#include "Draw/ModelData/ModelLoader.hpp"

#include "Draw/Types.h"

namespace tinygltf {
    class Accessor;
    class Animation;
    class AnimationChannel;
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

class ModelLoaderGltf : public ModelLoader {
public:
    ModelLoaderGltf();
    virtual ~ModelLoaderGltf();

    void load(Model &dst,
              const std::string &path,
              std::vector<std::string> &errors) const override;

private:
    std::unique_ptr<tinygltf::Model>
    _loadGltfModel(const std::string &path,
                   std::vector<std::string> &errors) const;

    void _loadBuffer(const tinygltf::Accessor &gltf_accessor,
                     const tinygltf::Model &gltf_model,
                     Model &model,
                     std::vector<std::string> &errors) const;

    void _loadTexture(const tinygltf::Texture &gltf_texture,
                      const tinygltf::Model &gltf_model,
                      Model &model,
                      std::vector<std::string> &errors) const;

    void _loadMaterial(const tinygltf::Material &gltf_material,
                       const tinygltf::Model &gltf_model,
                       Model &model,
                       std::vector<std::string> &errors) const;

    void _loadMesh(const tinygltf::Mesh &gltf_mesh,
                   const tinygltf::Model &gltf_model,
                   Model &model,
                   std::vector<std::string> &errors) const;

    void _loadPrimitive(const tinygltf::Primitive &gltf_prim,
                        const tinygltf::Model &gltf_model,
                        const Model &model,
                        Mesh &mesh,
                        std::vector<std::string> &errors) const;

    void _loadNode(const tinygltf::Node &gltf_node,
                   const tinygltf::Model &gltf_model,
                   Model &model,
                   std::vector<std::string> &errors) const;

    void _loadScene(const tinygltf::Scene &gltf_scene,
                    const tinygltf::Model &gltf_model,
                    Model &model,
                    std::vector<std::string> &errors) const;

    void _linkNodes(const tinygltf::Model &gltf_model,
                    Model &model,
                    std::vector<std::string> &errors) const;

    void _loadAnimation(const tinygltf::Animation &gltf_anim,
                        const tinygltf::Model &gltf_model,
                        Model &model,
                        std::vector<std::string> &errors) const;

    void _loadAnimationChannel(const tinygltf::AnimationChannel &gltf_chan,
                               const tinygltf::Animation &gltf_anim,
                               const tinygltf::Model &gltf_model,
                               const Model &model,
                               Animation &anim,
                               std::vector<std::string> &errors) const;

    template<typename T>
    using GetterType = void (ModelLoaderGltf::*)(const T &,
                                                 const tinygltf::Model &,
                                                 Model &,
                                                 std::vector<std::string> &) const;

    template<typename T, typename V>
    void _iterate(const std::vector<V> &gltf_list,
                  const tinygltf::Model &gltf_model,
                  GetterType<V> getter,
                  Model &model,
                  std::vector<std::string> &errors) const {

        for (int i = 0; i < gltf_list.size(); ++i){
            auto &gltf_obj = gltf_list[i];
            int err_count = errors.size();
            (this->*getter)(gltf_obj, gltf_model, model, errors);

            for (int j = err_count; j < errors.size(); j++){
                errors[j] = toString<T>() + "[" + std::to_string(j) + "]: " + errors[j];
            }
        }
    }
};

}