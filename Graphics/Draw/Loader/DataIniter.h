#pragma once

#include <memory>

#include "Draw/Mesh.h"
#include "Draw/Model.h"
#include "Draw/Node.h"
#include "Draw/Scene.h"
#include "Draw/Primitive.h"
#include "Draw/Texture.h"

namespace Graphics::Draw {

class DataIniter {
public:
    DataIniter() = default;
    virtual ~DataIniter() = default;

    virtual std::shared_ptr<Node> newNode(const glm::mat4 &mat) const = 0;
    virtual std::shared_ptr<Node> newNode(const glm::vec3 &translation,
                                          const glm::quat &rotation,
                                          const glm::vec3 &scale) const = 0;
    virtual std::shared_ptr<Scene> newScene() const = 0;
    virtual std::shared_ptr<Model> newModel() const = 0;
    virtual std::shared_ptr<Buffer> newBuffer(BufferType type,
                                              BufferElemType elem_type, BufferElemStruct elem_struct,
                                              size_t count, size_t bytes, bool normalized) const  = 0;
    virtual std::shared_ptr<Primitive> newPrimitive() const = 0;
    virtual std::shared_ptr<Texture> newTexture(int width, int height, int channels, int bpp) const = 0;
};

}