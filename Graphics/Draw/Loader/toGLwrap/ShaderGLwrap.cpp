#include "Draw/Loader/toGLwrap/ShaderGLwrap.h"

#include "magic_enum.h"

#include "GLwrap/Program.h"
#include "GLwrap/Shader.h"

using namespace Graphics::Draw;

ShaderGLwrap::ShaderGLwrap(const std::string &vertex_source,
                           const std::string &fragment_source) :
    Shader(){

    auto vert = std::make_shared<GLwrap::Shader>(GLwrap::ShaderType::Vertex, vertex_source);
    auto frag = std::make_shared<GLwrap::Shader>(GLwrap::ShaderType::Fragment, fragment_source);
    program = std::make_shared<GLwrap::Program>(std::vector({vert, frag}));
}

ShaderGLwrap::~ShaderGLwrap(){
}

bool ShaderGLwrap::verify() const {
    auto attr_count = magic_enum::enum_count<PrimitiveAttribute>();

    bool verified = true;
    std::vector<std::string> errors;

    for (int i = 0; i < attr_count; ++i){
        auto attr = magic_enum::enum_value<PrimitiveAttribute>(i);
        auto attr_name = toString(attr);

        auto loc = program->getAttribLoc(attr_name);
        if (loc != getLocation(attr)){
            errors.push_back("Shader attribute \"" + attr_name + "\" not found.");
            verified = false;
        }
    }

    return verified;
}

void ShaderGLwrap::draw(const Object &obj) const {

}