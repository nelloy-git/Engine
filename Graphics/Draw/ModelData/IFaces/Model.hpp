#pragma once

#include <string>

#include "Draw/ModelData/IFaces/Animation.hpp"
#include "Draw/ModelData/IFaces/Buffer.hpp"
#include "Draw/ModelData/IFaces/Material.hpp"
#include "Draw/ModelData/IFaces/Mesh.hpp"
#include "Draw/ModelData/IFaces/Node.hpp"
#include "Draw/ModelData/IFaces/Scene.hpp"
#include "Draw/ModelData/IFaces/Texture.hpp"

namespace Graphics::Draw {

class Model {
friend class ModelLoader;

public:
    Model() = default;
    virtual ~Model() = 0;

    template<typename T>
    using ref = std::shared_ptr<T>;

    const std::vector<ref<Animation>> &animations() const;
    const std::vector<ref<Buffer>> &buffers() const;
    const std::vector<ref<Texture>> &textures() const;
    const std::vector<ref<Material>> &materials() const;
    const std::vector<ref<Mesh>> &meshes() const;
    const std::vector<ref<Node>> &nodes() const;
    const std::vector<ref<Scene>> &scenes() const;

    virtual ref<Animation> addAnimation() = 0;
    virtual ref<Buffer> addBuffer(BufferType type,
                                  BufferElemType data_type,
                                  BufferElemStruct data_struct,
                                  size_t count,
                                  size_t bytes,
                                  bool normalized) = 0;
                              
    virtual ref<Texture> addTexture(int width,
                                    int height,
                                    int channels,
                                    int bpp) = 0;

    virtual ref<Material> addMaterial() = 0;
    virtual ref<Mesh> addMesh() = 0;
    virtual ref<Node> addNode(const glm::mat4 &mat) = 0;
    virtual ref<Node> addNode(const glm::vec3 &trans,
                              const glm::quat &rot,
                              const glm::vec3 &scale) = 0;
    virtual ref<Scene> addScene() = 0;

protected:
    std::vector<ref<Animation>> _animations;
    std::vector<ref<Buffer>> _buffers;
    std::vector<ref<Texture>> _textures;
    std::vector<ref<Material>> _materials;
    std::vector<ref<Mesh>> _meshes;
    std::vector<ref<Node>> _nodes;
    std::vector<ref<Scene>> _scenes;
};

}