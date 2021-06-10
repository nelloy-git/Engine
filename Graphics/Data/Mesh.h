#pragma once

#include "Data/glTF.h"
#include "Data/ModelBuffer.h"
#include "Data/Primitive.h"

namespace Graphics {

class Mesh {
public:
    Mesh(const tinygltf::Model &model,
         const tinygltf::Mesh &mesh,
         const ModelBuffer &buffer);
    virtual ~Mesh();

private:
    std::vector<std::shared_ptr<Primitive>> __primitives;
};

}