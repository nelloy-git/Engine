#pragma once

#include <memory>

#include "glad/gl.h"

#include "GLwrap/Buffer.h"
#include "GLwrap/Shader.h"

namespace GLwrap {

class BufferAttrubute {
public:

    // if (step == 0){step = size * sizeof(type)}
    BufferAttrubute(std::shared_ptr<Buffer> buffer, GLuint loc,
                    ShaderDataSize size, ShaderDataType type,
                    bool normalized, size_t step = 0, size_t offset = 0);
    ~BufferAttrubute();

    void enable(bool f);

private:
    std::shared_ptr<Buffer> __buffer;
    GLuint __layout_loc;
    ShaderDataSize __data_size;
    ShaderDataType __data_type;
    bool __normalized;
    size_t __step;
    size_t __offset;
};

}