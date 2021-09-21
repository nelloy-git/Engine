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

void BufferArray::bind() const {
    glBindVertexArray(id);
}

void BufferArray::unbind() const {
    glBindVertexArray(0);
}

void BufferArray::draw(DrawMode mode) const {
    glBindVertexArray(id);
    if (indexed){
        glDrawElements(static_cast<GLenum>(mode),
                       _vertex_count,
                       static_cast<GLenum>(_indices_type.value()),
                       (void*)0);
    } else {
        glDrawArrays(static_cast<GLenum>(mode), 0, _vertex_count);    
    }
}

GLuint BufferArray::_newId(){
    GLuint id;
    glGenVertexArrays(1, &id);
    return id;
}

void BufferArray::_bindBuffers(const Buffer *data,
                               const std::unordered_map<Layout, const BufferAccessor *> *accessors,
                               const std::optional<const Buffer *> indices){
    
    glBindVertexArray(id);

    data->bind();
    for (auto iter : *accessors){
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