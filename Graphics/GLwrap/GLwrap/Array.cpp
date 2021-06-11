#include "GLwrap/Array.h"

#include <unordered_map>

#include "Log.h"

using namespace GLwrap;

Array::Array(){
    glGenVertexArrays(1, &__id);
}

Array::~Array(){
    if (__id != 0){
        glDeleteVertexArrays(1, &__id);
    }
}

bool Array::load(std::shared_ptr<Elements> indices, 
                 const std::vector<std::pair<std::shared_ptr<Buffer>,
                                             std::shared_ptr<Accessor>>> &layouts){
                                                 
    bool valid = indices != nullptr;
    for (auto &pair : layouts){
        valid = valid && pair.first != nullptr && pair.second != nullptr;
    }
    if (!valid){
        LOG(WRN) << "some of pointers are nullptrs.";
        return false;
    }

    if (__id != 0){
        glDeleteVertexArrays(1, &__id);
        glGenVertexArrays(1, &__id);
    }

    __indices = indices;
    __layouts = layouts;
    
    glBindVertexArray(__id);

    std::unordered_map<int, bool> used_locs;

    for (auto &layout : layouts){
        int loc = layout.second->location;
        if (used_locs.find(loc) != used_locs.end()){
            LOG(WRN) << "layout location " << loc << " used at least second time.";
            continue;
        }

        layout.second->enable(*layout.first);
    }
    indices->bind();

    glBindVertexArray(0);
}

void Array::draw(DrawMode mode, ComponentType type, int count, size_t offset){
    glBindVertexArray(__id);
    count = count == 0 ? __indices->size / getDataTypeSize(type) : count;
    glDrawElements(static_cast<GLenum>(mode), count, static_cast<GLenum>(type), (void*)offset);
}

void Array::bind(){
    glBindVertexArray(__id);
}

void Array::unbind(){
    glBindVertexArray(0);
}