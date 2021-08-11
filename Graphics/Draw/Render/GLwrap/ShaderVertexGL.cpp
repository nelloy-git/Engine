#include "Draw/Render/GLwrap/ShaderVertexGL.hpp"

using namespace Graphics::Renderer;

ShaderVertexGL::ShaderVertexGL(const std::string &src = _getDefaultSrc()) :
    gl(GLwrap::ShaderType::Vertex, src){
}

ShaderVertexGL::~ShaderVertexGL(){
}

const std::string &ShaderVertexGL::_getDefaultSrc(){
    static std::string src =
        #include "Draw/Render/GLwrap/base.vert.glsl"
    ;
    return src;
}