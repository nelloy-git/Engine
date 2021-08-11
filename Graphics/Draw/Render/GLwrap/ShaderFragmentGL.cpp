#include "Draw/Render/GLwrap/ShaderFragmentGL.hpp"

using namespace Graphics::Renderer;

ShaderFragmentGL::ShaderFragmentGL(const std::string &src = _getDefaultSrc()) :
    gl(GLwrap::ShaderType::Fragment, src){
}

ShaderFragmentGL::~ShaderFragmentGL(){
}

const std::string &ShaderFragmentGL::_getDefaultSrc(){
    static std::string src =
        #include "Draw/Render/GLwrap/base.frag.glsl"
    ;
    return src;
}