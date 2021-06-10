#pragma once

#include <map>
#include <memory>
#include <stdexcept>

#include "tiny_gltf.h"

#include "Data/Primitive_glTF.h"

namespace Graphics {

// vertices     layout = 0
// normals      layout = 1
class Mesh_glTF {
public:
    Mesh_glTF(const tinygltf::Model &model, const tinygltf::Mesh &mesh);
    virtual ~Mesh_glTF();

    void draw();

private:
    std::vector<std::shared_ptr<Primitive_glTF>> __primitives;
};

}