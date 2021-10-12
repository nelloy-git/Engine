#pragma once

#include <memory>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLwrap/Program.hpp"
#include "GLwrap/Shader.hpp"

// #include "Graphics/Render/Base/Primitive.hpp"
// #include ""

namespace Graphics::Render::Base {


class VShader : public glw::Shader {
public:
    explicit VShader(const std::string &src) : glw::Shader(glw::ShaderType::Vertex, src){};
    VShader(const VShader &) = delete;
    virtual ~VShader(){}; // = 0;
};
// inline VShader::~VShader(){};


class FShader : public glw::Shader {
public:
    explicit FShader(const std::string &src) : glw::Shader(glw::ShaderType::Fragment, src){};
    FShader(const FShader &) = delete;
    virtual ~FShader(){}; // = 0;
};
// inline FShader::~FShader(){};


template<VertexStruct S>
class Renderer {
public:
    Renderer(const VShader &vert, const FShader &frag) :
        _gl_program(new glw::Program({&vert, &frag})){
    };
    Renderer(const Renderer &) = delete;
    virtual ~Renderer(){};

    inline virtual void use(){
        _gl_program->use();
    }

    void virtual enableTexture(const Texture &texture, int layer){
        texture.enable(layer);
    };

    // void virtual draw(const Primitive<S> &primitive,
    //                   const glm::mat4 &pose,
    //                   const std::vector<float> &morph) const = 0;

protected:
    std::unique_ptr<glw::Program> _gl_program;
};

}