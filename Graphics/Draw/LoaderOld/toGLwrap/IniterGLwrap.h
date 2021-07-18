#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Draw/Loader/DataIniter.h"

namespace Graphics::Draw {

class IniterGLwrap : public DataIniter {

public:
    IniterGLwrap();
    virtual ~IniterGLwrap();

    virtual std::shared_ptr<Node> newNode(const glm::mat4 &mat) const override;
    virtual std::shared_ptr<Node> newNode(const glm::vec3 &translation,
                                          const glm::quat &rotation,
                                          const glm::vec3 &scale) const override;
    virtual std::shared_ptr<Scene> newScene() const override;
    virtual std::shared_ptr<Shader> newShader(const std::vector<std::string> &sources) const override;
    virtual std::shared_ptr<Model> newModel() const override;
    virtual std::shared_ptr<Buffer> newBuffer(BufferType type,
                                      BufferElemType elem_type,
                                      BufferElemStruct elem_struct,
                                      size_t count,
                                      size_t bytes,
                                      bool normalized) const override;
    virtual std::shared_ptr<Primitive> newPrimitive() const override;
    virtual std::shared_ptr<Texture> newTexture(int width, int height, int channels, int bpp) const override;
};

}