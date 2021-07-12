#pragma once

#include "Draw/Loader/DataIniter.h"

#include "Draw/Buffer.h"
#include "Draw/Model.h"
#include "Draw/Primitive.h"
#include "Draw/Texture.h"

namespace Graphics::Draw {

class IniterGLwrap : public DataIniter {

public:
    IniterGLwrap();
    virtual ~IniterGLwrap();

    std::shared_ptr<Model> newModel() override;
    std::shared_ptr<Model> newModel() const override;

    std::shared_ptr<Buffer> newBuffer(BufferType type,
                                      BufferElemType elem_type,
                                      BufferElemStruct elem_struct,
                                      size_t count,
                                      size_t bytes,
                                      bool normalized) override;
    std::shared_ptr<Buffer> newBuffer(BufferType type,
                                      BufferElemType elem_type,
                                      BufferElemStruct elem_struct,
                                      size_t count,
                                      size_t bytes,
                                      bool normalized) const override;

    std::shared_ptr<Primitive> newPrimitive() override;
    std::shared_ptr<Primitive> newPrimitive() const override;

    std::shared_ptr<Texture> newTexture(int width, int height, int channels, int bpp) override;
    std::shared_ptr<Texture> newTexture(int width, int height, int channels, int bpp) const override;
};

}