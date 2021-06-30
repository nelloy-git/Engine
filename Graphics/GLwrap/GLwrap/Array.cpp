#include "GLwrap/Array.h"

#include <unordered_map>

#include "Log.h"

using namespace GLwrap;

Array::Array(std::shared_ptr<Buffer> indices, 
             const std::unordered_map<int, BufferPair> &layouts) :
    indices(indices),
    layouts(layouts)
{
    glGenVertexArrays(1, &_id);
    glBindVertexArray(_id);

    for (int loc = 0; loc < layouts.size(); loc++){
        layouts.at(loc).first->bind();
        layouts.at(loc).second->enable(loc);
    }
    indices->bind();

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

void Array::draw(DrawMode mode, ComponentType type, size_t vertex_count, size_t byte_offset) {
    glBindVertexArray(_id);
    glDrawElements(static_cast<GLenum>(mode), vertex_count,
                   static_cast<GLenum>(type), (void*)byte_offset);
}