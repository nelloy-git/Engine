#pragma once

#include "Data/glTF.h"
#include "Data/ModelData.h"
#include "Data/Primitive.h"

namespace Graphics {

class Mesh {
public:
    Mesh(const tinygltf::Model &model,
         const tinygltf::Mesh &mesh,
         const ModelData &buffer);
    virtual ~Mesh();

    void draw();
    
    std::vector<std::shared_ptr<Primitive>> primitives;

private:
};

}