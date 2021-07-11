#pragma once

#include "Model/Buffer.h"
#include "Model/Model.h"
#include "Model/Primitive.h"
#include "Model/Texture.h"

namespace Graphics::Model::Creator {

std::shared_ptr<Model> newModel(const std::string &path);

std::shared_ptr<Buffer> newBuffer(BufferType type,
                                  BufferElemType elem_type,
                                  BufferElemStruct elem_struct,
                                  int count,
                                  int bytes,
                                  bool normalized);

std::shared_ptr<Primitive> newPrimitive();

std::shared_ptr<Texture> newTexture(int width, int height, int channels, int bpp);

}