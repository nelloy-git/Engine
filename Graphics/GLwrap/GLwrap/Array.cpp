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

GLint Array::max_layouts(){
    static const GLint max = getMaxLayouts();
    return max;
}

Array::Array(const Buffer &indices, 
             const std::unordered_map<int, BufferPair> &layouts){
    glGenVertexArrays(1, &_id);
    glBindVertexArray(_id);

    for (auto iter : layouts){
        auto loc = iter.first;
        if (loc > Array::max_layouts()){
            continue;
        }

        iter.second.first->bind();
        iter.second.second->enable(loc);
    }
    
    indices.bind();

    glBindVertexArray(0);
}

Array::Array(const std::unordered_map<int, BufferPair> &layouts){
    glGenVertexArrays(1, &_id);
    glBindVertexArray(_id);

    for (auto iter : layouts){
        auto loc = iter.first;
        if (loc > Array::max_layouts()){
            continue;
        }

        iter.second.first->bind();
        iter.second.second->enable(loc);
    }

    glBindVertexArray(0);
}

Array::~Array(){
    glDeleteVertexArrays(1, &_id);
}

void Array::bind(){
    glBindVertexArray(_id);
}

void Array::unbind(){
    glBindVertexArray(0);
}

void Array::bind() const {
    glBindVertexArray(_id);
}

void Array::unbind() const {
    glBindVertexArray(0);
}

void Array::drawArrays(DrawMode mode, GLuint first, GLuint count){
    glBindVertexArray(_id);
    glDrawArrays(static_cast<GLenum>(mode), first, count);
    glBindVertexArray(0);
}

void Array::drawElements(DrawMode mode, ComponentType type, GLuint vertex_count, GLuint64 byte_offset) {
    glBindVertexArray(_id);
    glDrawElements(static_cast<GLenum>(mode), vertex_count,
                   static_cast<GLenum>(type), (void*)byte_offset);
    glBindVertexArray(0);
}