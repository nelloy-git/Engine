#pragma once

#include "Draw/ModelData/IFaces/Model.hpp"

namespace Graphics::Draw {

class ModelGL : public Model {
public:
    ModelGL();
    virtual ~ModelGL();

protected:
    virtual Animation *_addAnimation() override;
    virtual Buffer *_addBuffer(BufferType type,
                              BufferElemType data_type,
                              BufferElemStruct data_struct,
                              size_t count,
                              size_t bytes,
                              bool normalized) override;
    virtual Texture *_addTexture(int width,
                                int height,
                                int channels,
                                int bpp) override;
    virtual Material *_addMaterial() override;
    virtual Mesh *_addMesh() override;
    virtual Node *_addNode(const glm::mat4 &mat) override;
    virtual Node *_addNode(const glm::vec3 &trans,
                          const glm::quat &rot,
                          const glm::vec3 &scale) override;
    virtual Scene *_addScene() override;

    template<typename R, typename T, typename ... Args>
    inline R *_addObj(std::vector<Uptr<T>> &list, Args&& ...args){
        auto raw = new R(this, list.size(), std::forward<Args>(args)...);
        list.emplace_back(raw);
        return raw;
    }
};

}