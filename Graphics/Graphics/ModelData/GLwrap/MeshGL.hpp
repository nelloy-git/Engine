#pragma once

#include "Graphics/ModelData/IFaces/Mesh.hpp"

namespace Graphics::Draw {

class MeshGL : public Mesh {

public:
    MeshGL(const Model *model, int index);
    ~MeshGL();

protected:
    Primitive *_addPrimitive() override;
};

}