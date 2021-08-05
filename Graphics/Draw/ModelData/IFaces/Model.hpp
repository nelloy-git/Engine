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
    using Ref = std::shared_ptr<T>;

    const std::vector<Ref<Animation>> &animations() const;
    const std::vector<Ref<Buffer>> &buffers() const;
    const std::vector<Ref<Texture>> &textures() const;
    const std::vector<Ref<Material>> &materials() const;
    const std::vector<Ref<Mesh>> &meshes() const;
    const std::vector<Ref<Node>> &nodes() const;
    const std::vector<Ref<Scene>> &scenes() const;

    virtual Ref<Animation> addAnimation() = 0;
    virtual Ref<Buffer> addBuffer(BufferType type,
                                  BufferElemType data_type,
                                  BufferElemStruct data_struct,
                                  size_t count,
                                  size_t bytes,
                                  bool normalized) = 0;
                              
    virtual Ref<Texture> addTexture(int width,
                                    int height,
                                    int channels,
                                    int bpp) = 0;

    virtual Ref<Material> addMaterial() = 0;
    virtual Ref<Mesh> addMesh() = 0;
    virtual Ref<Node> addNode(const glm::mat4 &mat) = 0;
    virtual Ref<Node> addNode(const glm::vec3 &trans,
                              const glm::quat &rot,
                              const glm::vec3 &scale) = 0;
    virtual Ref<Scene> addScene() = 0;

protected:
    std::vector<Ref<Animation>> _animations;
    std::vector<Ref<Buffer>> _buffers;
    std::vector<Ref<Texture>> _textures;
    std::vector<Ref<Material>> _materials;
    std::vector<Ref<Mesh>> _meshes;
    std::vector<Ref<Node>> _nodes;
    std::vector<Ref<Scene>> _scenes;
};

}