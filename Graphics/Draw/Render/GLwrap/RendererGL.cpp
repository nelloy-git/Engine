#include "Draw/Render/GLwrap/RendererGL.hpp"

using namespace Graphics::Render;

RendererGL::RendererGL(const std::string *input = nullptr,
                       const std::string *vertex = nullptr,
                       const std::string *fragment = nullptr) :
    Renderer(){
    
    _input_shader = std::make_unique<ShaderInputGL>(input);
    _vertex_shader = std::make_unique<ShaderVertexGL>(vertex);
    _fragment_shader = std::make_unique<ShaderFragmentGL>(fragment);

    std::vector<const GLwrap::Shader *> list = {
        &_input_shader->gl,
        &_vertex_shader->gl,
        &_fragment_shader->gl,
    };
    _gl = std::make_unique<GLwrap::Program>(list);
}

RendererGL::~RendererGL(){
}