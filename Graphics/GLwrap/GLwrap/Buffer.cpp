#include "GLwrap/Buffer.h"

#include <stdexcept>

using namespace GLwrap;

Buffer::Buffer(BufferType type, size_t size, BufferUsage usage) : 
    type(type),
    size(size),
    usage(usage){

    glGenBuffers(1, &__id);

    glBindBuffer(static_cast<GLenum>(type), __id);
    glBufferData(static_cast<GLenum>(type), size, nullptr, static_cast<GLenum>(usage));
    glBindBuffer(static_cast<GLenum>(type), 0);
}

Buffer::~Buffer(){
    glDeleteBuffers(1, &__id);
}

GLuint Buffer::id(){
    return __id;
}

void Buffer::load(const void* data, int offset, size_t size){
    if (size == 0){
        size = this->size;
    } else if (offset + size > this->size){
        std::string head(typeid(this).name());
        head += ".";
        head += __func__;
        throw std::invalid_argument(head + ": data is outside of buffer size.");
    }

    glBindBuffer(static_cast<GLenum>(type), __id);
    glBufferSubData(static_cast<GLenum>(type), offset, size, data);
    glBindBuffer(static_cast<GLenum>(type), 0);
}

// void Buffer::attrib(GLuint layout_loc, ShaderDataSize size, ShaderDataType type,
//                     size_t step = 0, size_t offset = 0){
//     if (step == 0){
//         step = static_cast<GLuint>(size) * Shader::getDataTypeSize(type);
//     }

//     glBindBuffer(static_cast<GLenum>(type), __id);
//     glEnableVertexAttribArray(layout_loc);
//     glVertexAttribPointer(layout_loc,
//                           static_cast<GLuint>(size),
//                           static_cast<GLenum>(type),
//                           GL_FALSE, step, (void*)offset);
//     glBindBuffer(static_cast<GLenum>(type), 0);
// }

// void Buffer::attrib(const BufferAttrubute &attr){
//     attrib(attr.layout_loc, attr.data_size, attr.data_type, attr.step, attr.offset);
// }

void Buffer::bind() const {
    glBindBuffer(static_cast<GLenum>(type), __id);
}

void Buffer::unbind() const {
    glBindBuffer(static_cast<GLenum>(type), 0);
}