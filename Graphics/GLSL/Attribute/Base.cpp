#include "GLSL/Attribute/Base.h"

#include <stdexcept>

using namespace Graphics::GLSL::Attribute;

Base::Base(const std::shared_ptr<Program> program, const std::string& attr_name) :
    program(program),
    name(attr_name),
    id(glGetAttribLocation(program->id, attr_name.c_str())){

    if (id == -1){
        std::string msg = "Graphics::GLSL::Attribute::Base " + name + " name is not available";
        printf(name.c_str());
        throw std::invalid_argument(msg.c_str());
    }
}