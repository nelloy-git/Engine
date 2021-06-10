#include "GLwrap/BufferAttribute.h"

using namespace GLwrap;

BufferAttrubute::BufferAttrubute(std::shared_ptr<Buffer> buffer, GLuint loc,
                                 ShaderDataSize size, ShaderDataType type,
                                 bool normalized, size_t step, size_t offset){
    __buffer = buffer;
    __layout_loc = loc;
    __data_size = size;
    __data_type = type;
    __normalized = normalized;
    __step = step == 0 ? static_cast<GLuint>(size) * Shader::getDataTypeSize(type) : step;
    __offset = offset;
}

BufferAttrubute::~BufferAttrubute(){
    
}

void BufferAttrubute::enable(bool f){
    __buffer->bind();
    if (!f){
        glDisableVertexAttribArray(__layout_loc);
        __buffer->unbind();
        return;
    }

    glEnableVertexAttribArray(__layout_loc);
    glVertexAttribPointer(__layout_loc,
                          static_cast<GLuint>(__data_size),
                          static_cast<GLenum>(__data_type),
                          __normalized ? GL_TRUE : GL_FALSE,
                          __step, (void*)__offset);
    __buffer->unbind();
}