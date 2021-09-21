#include "GLwrap/Array.h"

#include <stdexcept>
#include <unordered_map>

#include "Log.h"

using namespace GLwrap;

GLint getMaxLayouts(){
    GLint _max;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &_max);
    return _max;
}

GLint BufferArray::max_layouts(){
    static const GLint max = getMaxLayouts();
    return max;
}

BufferArray::~BufferArray(){
    glDeleteVertexArrays(1, &id);
}

GLuint BufferArray::_newId(){
    GLuint id;
    glGenVertexArrays(1, &id);
    return id;
}

void BufferArray::_bindBuffers(const Buffer &data,
                               const std::unordered_map<Layout, const BufferAccessor *> &accessors,
                               const std::optional<const Buffer *> indices){
    
    glBindVertexArray(id);

    data.bind();
    for (auto iter : accessors){
        auto loc = iter.first;
        if (loc > BufferArray::max_layouts()){
            continue;
        }

        auto acc = iter.second;
        if (acc) acc->enable(loc);
    }

    if (indices){
        indices.value()->bind();
    }
    glBindVertexArray(0);
}