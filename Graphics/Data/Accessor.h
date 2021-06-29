#pragma once

#include "GLwrap/BufferAccessor.h"

#include "Data/glTF.h"

namespace Graphics {

class ModelData;

class Accessor {
public:
    Accessor(const tinygltf::Model &model,
                 const tinygltf::Accessor &acc,
                 ModelData &data);
    virtual ~Accessor();

    std::shared_ptr<GLwrap::BufferAccessor> accessor;
};

}