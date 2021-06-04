#include "GLSL/Program.h"

using namespace Graphics::GLSL;

Program::Program(const std::vector<std::shared_ptr<Shader>>& attach){
    auto pId = const_cast<GLuint*>(&id);
    *pId = glCreateProgram();

    for (auto shader : attach){
        glAttachShader(id, shader->id);
    }
    glLinkProgram(id);
}

Program::~Program(){
    glDeleteProgram(id);
}

bool Program::linkVertexArray(const std::string &attr_name, const VBO::Array &vbo,
                              DataSize size, DataType type, bool normalize,
                              size_t step, void* first_offset){
    
    auto attr_id = glGetAttribLocation(id, attr_name.c_str());
    if (attr_id == -1){return false;}

    vbo.bind();
    glEnableVertexAttribArray(attr_id);
    glVertexAttribPointer(attr_id, static_cast<GLint>(size), static_cast<GLenum>(type),
                          normalize ? GL_TRUE : GL_FALSE,
                          step, first_offset);
    vbo.unbind();
};

bool Program::linkFVec2Array(const std::string &attr_name, const VBO::Array &vbo,
                              size_t step, void* first_offset){
    return linkVertexArray(attr_name, vbo, DataSize::Vec2, DataType::Float, false, step, first_offset);
}

bool Program::linkFVec3Array(const std::string &attr_name, const VBO::Array &vbo,
                              size_t step, void* first_offset){
    return linkVertexArray(attr_name, vbo, DataSize::Vec3, DataType::Float, false, step, first_offset);
}