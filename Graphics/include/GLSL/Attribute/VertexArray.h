#pragma once

#include "glad/glad.h"

#include "GLSL/Attribute/Base.h"
#include "GLSL/Program.h"

namespace Graphics::GLSL::Attribute {

template<typename ...Args>
class VertexArray : public Base {
public:
    VertexArray(const Program& program, const std::string& name, ... Args);
    virtual ~VertexArray();

    const GLuint id = 0;

private:
};

}