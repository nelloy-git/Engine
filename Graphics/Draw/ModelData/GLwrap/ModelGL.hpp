#pragma once

#include "Draw/ModelData/IFaces/Model.hpp"

namespace Graphics::Draw {

class ModelGL : public Model {
public:
    ModelGL();
    virtual ~ModelGL() override;

    virtual Ref<Animation> addAnimation() override;
    virtual Ref<Buffer> addBuffer(BufferType type,
                                  BufferElemType data_type,
                                  BufferElemStruct data_struct,
                                  size_t count,
                                  size_t bytes,
                                  bool normalized) override;
                              
    virtual Ref<Texture> addTexture(int width,
                                    int height,
                                    int channels,
                                    int bpp) override;

    virtual Ref<Material> addMaterial() override;
    virtual Ref<Mesh> addMesh() override;
    virtual Ref<Node> addNode(const glm::mat4 &mat) override;
    virtual Ref<Node> addNode(const glm::vec3 &trans,
                              const glm::quat &rot,
                              const glm::vec3 &scale) override;
    virtual Ref<Scene> addScene() override;

    template<typename R, typename T, typename ...ARGS>
    inline Ref<R> _addObj(std::vector<T> &list, ARGS ...args){
        int index = list.size();
        auto obj = std::make_shared<R>(*this, index, args...);
        list.push_back(obj);
        return obj;
    }
};

}