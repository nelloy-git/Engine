#pragma once

#include <memory>

#include "glad/glad.h"

#include "GLSL/Program.h"

namespace Graphics::GLSL::Attribute {

class Base {
public:
    Base(const std::shared_ptr<Program> program, const std::string& attr_name);
    virtual ~Base(){};

    const GLuint id = 0;
    const std::shared_ptr<Program> program;
    const std::string name;

private:
};

}