#include "GLwrap/Vao.h"

using namespace GLwrap;

VAO::VAO(){
    glGenVertexArrays(1, &__id);
}

VAO::~VAO(){
    glDeleteVertexArrays(1, &__id);
}

void VAO::load(const AttrList &attrs, std::shared_ptr<VEO> veo){
    glBindVertexArray(__id);

    for (auto vbo : __vbos){
        vbo->unbind();
    }
    __vbos.clear();

    if (__veo){
        __veo->unbind();
    }

    for (int i = 0; i < attrs.size(); i++){
        auto vbo = attrs[i].first;
        auto attr = attrs[i].second;

        __vbos.push_back(attrs[i].first);
        vbo->attrib(*attr);
        vbo->bind();
    }

    __veo = veo;
    __veo->bind();

    glBindVertexArray(0);
}

void VAO::bind(){
    glBindVertexArray(__id);
}

void VAO::unbind(){
    glBindVertexArray(0);
}