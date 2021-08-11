#include "Draw/Render/GLwrap/ShaderInputGL.hpp"

using namespace Graphics::Render;

ShaderInputGL::ShaderInputGL(const std::string *src) :
    ShaderInput(),
    gl(GLwrap::ShaderType::Vertex, src ? *src : _getDefaultSrc()){
}

ShaderInputGL::~ShaderInputGL(){
}

const std::string &ShaderInputGL::_getDefaultSrc(){
    static std::string src = 
        #include "Draw/Render/GLwrap/input.vert.glsl"
    ;
    return src;
}