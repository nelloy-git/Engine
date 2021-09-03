#pragma once

#include <memory>
#include <vector>

#include "Graphics/Render/PrimitiveGL.hpp"

#include "Graphics/Model/Mesh.hpp"
#include "Graphics/Model/Node.hpp"

namespace tinygltf {
    class Model;
    class Primitive;
}

namespace Graphics::Model {

class Animation;
class Buffer;
class Material;
class Scene;
class Texture;

class Model {
friend class ModelLoader;

public:
    // glTF2.0 only
    Model(const std::string &path);
    virtual ~Model();

    std::vector<std::unique_ptr<Animation>> animations;
    std::vector<std::unique_ptr<Buffer>> buffers;
    std::vector<std::unique_ptr<Material>> materials;
    std::vector<std::unique_ptr<Mesh>> meshes;
    std::vector<std::unique_ptr<Node>> nodes;
    std::vector<std::unique_ptr<Scene>> scenes;
    std::vector<std::unique_ptr<Texture>> textures;

    std::vector<std::vector<std::unique_ptr<Render::PrimitiveGL>>> primitives;

private:
    void _loadPrimitives(const tinygltf::Model &model);
    Render::PrimitiveGL *_loadPrimitive(const tinygltf::Model &model,
                                        const tinygltf::Primitive &primitive)


};

}