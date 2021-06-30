#pragma once

#include "Data/glTF.h"
#include "Data/Primitive.h"

namespace Graphics {

class ModelData;

class Mesh {
public:
    Mesh(const tinygltf::Mesh &mesh,
         ModelData &data);
    virtual ~Mesh();

    void draw();
    void draw() const;
    
    std::vector<std::shared_ptr<Primitive>> primitives;

private:
};

}