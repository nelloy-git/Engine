#include "GLwrap/Array.h"

#include <unordered_map>

#include "Log.h"

using namespace GLwrap;

Array::Array(std::shared_ptr<Buffer> indices, 
             const std::vector<std::pair<std::shared_ptr<Buffer>,
                                         std::shared_ptr<BufferAccessor>>> &layouts) :
    indices(indices),
    layouts(layouts)
{
    glGenVertexArrays(1, &_id);
    glBindVertexArray(_id);

    for (int loc = 0; loc < layouts.size(); loc++){
        layouts[loc].first->bind();
        layouts[loc].second->enable(loc);
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