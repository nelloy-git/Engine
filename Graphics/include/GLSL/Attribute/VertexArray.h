#pragma once

#include <memory>

#include "glad/glad.h"

#include "GLSL/Types.h"
#include "GLSL/Program.h"
#include "VBO/Array.h"

#include "GLSL/Attribute/Base.h"

namespace Graphics::GLSL::Attribute {

class VertexArray : public Base {
public:
    VertexArray(const std::shared_ptr<Program> program, const std::string& attr_name,
                const std::shared_ptr<VBO::Array> vbo,
                const DataSize size, const DataType type, const bool normalize,
                const GLsizei step, const int offset);
    virtual ~VertexArray(){};

    const std::shared_ptr<VBO::Array> vbo;
    const DataSize size;
    const DataType type;
    const bool normalize;
    const GLsizei step;
    const int offset;

private:


};

}