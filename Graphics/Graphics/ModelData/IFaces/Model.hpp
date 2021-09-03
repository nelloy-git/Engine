#pragma once

#include <string>

#include "Graphics/ModelData/IFaces/Animation.hpp"
#include "Graphics/ModelData/IFaces/Buffer.hpp"
#include "Graphics/ModelData/IFaces/Material.hpp"
#include "Graphics/ModelData/IFaces/Mesh.hpp"
#include "Graphics/ModelData/IFaces/Node.hpp"
#include "Graphics/ModelData/IFaces/Scene.hpp"
#include "Graphics/ModelData/IFaces/Texture.hpp"

namespace Graphics::Draw {

class Model {
friend class ModelLoader;

public:
    Model() = default;
    virtual ~Model() = default;

    Animation *getAnimation(int i) const;
    int getAnimationsCount() const;

    Buffer *getBuffer(int i) const;
    int getBuffersCount() const;

    Texture *getTexture(int i) const;
    int getTexturesCount() const;

    Material *getMaterial(int i) const;
    int getMaterialsCount() const;

    Mesh *getMesh(int i) const;
    int getMeshesCount() const;

    Node *getNode(int i) const;
    int getNodesCount() const;

    Scene *getScene(int i) const;
    int getScenesCount() const;


protected:
    virtual Animation *_addAnimation() = 0;
    virtual Buffer *_addBuffer(BufferType type,
                              BufferElemType data_type,
                              BufferElemStruct data_struct,
                              size_t count,
                              size_t bytes,
                              bool normalized) = 0;
    virtual Texture *_addTexture(int width,
                                int height,
                                int channels,
                                int bpp) = 0;
    virtual Material *_addMaterial() = 0;
    virtual Mesh *_addMesh() = 0;
    virtual Node *_addNode(const glm::mat4 &mat) = 0;
    virtual Node *_addNode(const glm::vec3 &trans,
                          const glm::quat &rot,
                          const glm::vec3 &scale) = 0;
    virtual Scene *_addScene() = 0;

    template<typename T>
    using Uptr = std::unique_ptr<T>;

    std::vector<Uptr<Animation>> _animations;
    std::vector<Uptr<Buffer>> _buffers;
    std::vector<Uptr<Texture>> _textures;
    std::vector<Uptr<Material>> _materials;
    std::vector<Uptr<Mesh>> _meshes;
    std::vector<Uptr<Node>> _nodes;
    std::vector<Uptr<Scene>> _scenes;

private:

    template<typename T>
    inline T *_getRawPtr(const std::vector<Uptr<T>> &list, int i) const {
        if (i < 0 || i >= list.size()){
            return nullptr;
        }
        return list[i].get();
    };
};

}