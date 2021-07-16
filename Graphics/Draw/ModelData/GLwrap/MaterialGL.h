#pragma once

#include <memory>

#include "Draw/ModelData/Material.h"
#include "Draw/ModelData/GLwrap/TextureGL.h"

namespace Graphics::Draw {

class MaterialGL : public Material {
public:
    MaterialGL();
    virtual ~MaterialGL();
};

}