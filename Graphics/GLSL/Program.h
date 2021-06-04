#pragma once

#include <memory>
#include <vector>

#include "glad/glad.h"

#include "GLSL/Shader.h"
#include "VBO/Array.h"

namespace Graphics::GLSL {

class Program {
public:
    Program(const std::vector<std::shared_ptr<Shader>> &attach);
    virtual ~Program();

    bool linkVertexArray(const std::string &attr_name, const VBO::Array &vbo,
                         DataSize size, DataType type, bool normalize,
                         size_t step, void* first_offset);

    // linkVertexArray with args:
    // DataSize size = DataSize::Vec2
    // DataType type = DataType::Float
    // bool normalize = false
    bool linkFVec2Array(const std::string &attr_name, const VBO::Array &vbo,
                        size_t step, void* first_offset);

    // linkVertexArray with args:
    // DataSize size = DataSize::Vec3
    // DataType type = DataType::Float
    // bool normalize = false
    bool linkFVec3Array(const std::string &attr_name, const VBO::Array &vbo,
                        size_t step, void* first_offset);

    const GLuint id = 0;

private:
    
};

}