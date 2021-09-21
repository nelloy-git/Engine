#pragma once

#include "Graphics/Render/Base/Renderer.hpp"

#include "Graphics/Render/Easy/Vertex.hpp"

namespace Graphics::Render::Easy {

class FShader : public Base::FShader {
public:
    using Vertex = Base::Vertex<VERT_STRUCT>;

    explicit FShader();
    FShader(const FShader &) = delete;
    virtual ~FShader() = default;

private:
    static const std::string &_getSource();

    static std::string _createSourceAll();
};

}