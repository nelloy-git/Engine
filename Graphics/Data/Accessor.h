#pragma once

#include "GLwrap/BufferAccessor.h"

#include "Data/glTF.h"
#include "Data/BufferView.h"

namespace Graphics {

class ModelData;

class Accessor {
public:
    Accessor(const tinygltf::Accessor &acc,
             ModelData &data);
    virtual ~Accessor();

    int count;
    std::shared_ptr<GLwrap::BufferAccessor> accessor;
    std::shared_ptr<BufferView> view;
};

}