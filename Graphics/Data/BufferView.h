#pragma once

#include "GLwrap/Buffer.h"

#include "Data/glTF.h"

namespace Graphics {

class ModelData;

class BufferView {
public:
    BufferView(const tinygltf::Model &model,
               const tinygltf::BufferView &view,
               ModelData &data);
    virtual ~BufferView();

    std::shared_ptr<GLwrap::Buffer> buffer;
};

}