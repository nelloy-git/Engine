#pragma once

#include "Draw/ModelData/IFaces/Mesh.hpp"

namespace Graphics::Draw {

class MeshGL : public Mesh {
public:
    MeshGL(const Model &model, int index);
    ~MeshGL();

    std::shared_ptr<Primitive> addPrimitive() override;
};

}