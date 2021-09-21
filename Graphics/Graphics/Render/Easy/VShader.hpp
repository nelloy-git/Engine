#pragma once

#include "Graphics/Render/Base/Renderer.hpp"

#include "Graphics/Render/Easy/Vertex.hpp"

namespace Graphics::Render::Easy {

class VShader : public Base::VShader {
public:
    using Vertex = Base::Vertex<VERT_STRUCT>;

    explicit VShader();
    VShader(const VShader &) = delete;
    virtual ~VShader() = default;

    enum class UniMat4 {
        ModelPose,
        Camera
    };
    static const std::string &getName(UniMat4 uniform);

protected:
    static const std::string &_getSource();

    static std::string _createInputSource();
    static std::string _createParseFuncSource(const std::string &name, int n_offset, GLwrap::ElementStruct gl_size);
    static std::string _createParseFuncSourceAll();
    static std::string _createSourceAll();
};

}