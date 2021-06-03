#include "GLSL/Attribute/Base.h"

#include <stdexcept>

using namespace Graphics::GLSL::Attribute;

Base::Base(const Program& program, const std::string& name) :
    name(name){
    auto pId = const_cast<GLuint*>(&id);
    *pId = glGetAttribLocation(program.id, name.c_str());

    if (id == -1){
        std::string msg = "Graphics::GLSL::Attribute::Base " + name + " name is not available";
        std::invalid_argument(msg.c_str());
    }
}