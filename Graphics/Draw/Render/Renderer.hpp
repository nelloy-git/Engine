#pragma once

#include <string>

#include "Draw/Render/ShaderIFaces.hpp"

namespace Graphics::Render {

class Renderer {
public:
    Renderer() = default;
    virtual ~Renderer(){};
};

}