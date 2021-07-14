#include "Draw/Loader/toGLwrap/ShaderGLwrap.h"

#include "Log.h"

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
    bool verified = true;
    auto log = LOG(MSG);

    constexpr auto attr_count = enumCount<PrimitiveAttribute>();
    log << "Attributes:\n";
    for (int i = 0; i < attr_count; ++i){
        auto attr = magic_enum::enum_value<PrimitiveAttribute>(i);
        auto attr_name = toString(attr);
        auto attr_loc = getLocation(attr);

        bool valid = attr_loc == program->getAttribLoc(attr_name);
        log << "\t\"" << attr_name << "\" "
            << (valid ? "found" : "NOT FOUND") << "\n";
        verified &= valid;
    }

    constexpr PrimitiveAttribute targets[] = {
        PrimitiveAttribute::Position,
        PrimitiveAttribute::Normal,
        PrimitiveAttribute::Tangent
    };

    log << "Morph targets:\n";
    for (int i = 0; i < 4; ++i){
        for (auto targ : targets){
            auto targ_name = getMorphTargetName(i, targ);
            auto targ_loc = getMorphTargetLocation(i, targ);

            bool valid = targ_loc == program->getAttribLoc(targ_name);
            log << "\t\"" << targ_name << "\" "
                << (valid ? "found" : "NOT FOUND") << "\n";
            verified &= valid;
        }
    }

    return verified;
}

void ShaderGLwrap::draw(const Object &obj) const {

}