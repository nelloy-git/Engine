#pragma once

#include "glad/glad.h"

#include "GLSL/Program.h"

namespace Graphics::GLSL::Attribute {

class Base {
public:
    Base(const Program& program, const std::string& name);
    virtual ~Base();

    const GLuint id = 0;
    const std::string name;

private:
};

}