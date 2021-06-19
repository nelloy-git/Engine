#pragma once

#include <vector>
#include <memory>
#include <utility>

#include "glad/gl.h"

#include "GLwrap/BufferAccessor.h"
#include "GLwrap/Buffer.h"

namespace GLwrap {

class Array {
public:
    Array(std::shared_ptr<Buffer> indices, 
          const std::vector<std::pair<std::shared_ptr<Buffer>,
                                      std::shared_ptr<BufferAccessor>>> &layouts);
    virtual ~Array();

    GLuint id();

    void bind();
    void unbind();
    
    void bind() const;
    void unbind() const;

    std::shared_ptr<Buffer> indices;
    std::vector<std::pair<std::shared_ptr<Buffer>,
                          std::shared_ptr<BufferAccessor>>> layouts;

private:
    GLuint _id = 0;
};

}