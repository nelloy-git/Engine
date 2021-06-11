#pragma once

#include <unordered_map>

#include "GLwrap/Array.h"

#include "Data/glTF.h"
#include "Data/ModelBuffer.h"

namespace Graphics {

class Primitive {
public:
    Primitive(const tinygltf::Model &model,
              const tinygltf::Primitive &primitive,
              const ModelBuffer &buffer);

    virtual ~Primitive();

    void draw();

private:
    std::shared_ptr<GLwrap::Array> __array;

    // int __count;
    GLwrap::DrawMode __mode;
    GLwrap::ComponentType __type;
};

}