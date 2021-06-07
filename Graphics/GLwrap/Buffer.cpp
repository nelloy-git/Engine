#include "GLwrap/Buffer.h"

using namespace Graphics::GLwrap;

Buffer::Buffer(BufferType type, size_t size, UsageType usage) :
    id(0),
    type(type),
    size(size),
    usage(usage){

    auto pId = const_cast<GLuint*>(&id);
    glGenBuffers(1, pId);

    glBindBuffer(static_cast<GLenum>(type), id);
    glBufferData(static_cast<GLenum>(type), size, nullptr, static_cast<GLenum>(usage));
    glBindBuffer(static_cast<GLenum>(type), 0);
}

Buffer::~Buffer(){
    glDeleteBuffers(1, &id);
}

void Buffer::load(const void* data, int offset, size_t size){
    if (size == 0){
        size = this->size;
    }

    glBindBuffer(static_cast<GLenum>(type), id);
    glBufferSubData(static_cast<GLenum>(type), offset, size, data);
    glBindBuffer(static_cast<GLenum>(type), 0);
}

void Buffer::attrib(GLuint attr_id,
                    ShaderDataSize attr_size, ShaderDataType attr_type,
                    size_t step, size_t offset){
    if (step == 0){
        step = static_cast<GLuint>(attr_size) * GLwrap::getShaderDataTypeSize(attr_type);
    }

    glBindBuffer(static_cast<GLenum>(type), id);
    glVertexAttribPointer(attr_id,
                          static_cast<GLuint>(attr_size),
                          static_cast<GLenum>(attr_type),
                          GL_FALSE, step, (void*)offset);
    glEnableVertexAttribArray(attr_id);
    glBindBuffer(static_cast<GLenum>(type), 0);
}

void Buffer::bind() const {
    glBindBuffer(static_cast<GLenum>(type), id);
}

void Buffer::unbind() const {
    glBindBuffer(static_cast<GLenum>(type), 0);
}