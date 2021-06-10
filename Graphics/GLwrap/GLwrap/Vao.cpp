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

    for (auto layout : __layouts){
        layout->enable(false);
    }
    __layouts.clear();

    if (__veo){
        __veo->unbind();
    }

    for (auto attr : attrs){
        __layouts.push_back(attr);
        attr->enable(true);
    }

    __veo = veo;
    __veo->bind();

    glBindVertexArray(0);
}

void VAO::draw(VAOdrawMode mode, int count, ShaderDataType component, size_t offset){
    glBindVertexArray(__id);
    glDrawElements(static_cast<GLenum>(mode), count, static_cast<GLenum>(component), (void*)offset);
}

void VAO::bind(){
    glBindVertexArray(__id);
}

void VAO::unbind(){
    glBindVertexArray(0);
}