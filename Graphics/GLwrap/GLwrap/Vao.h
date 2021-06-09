#pragma once

#include <vector>
#include <memory>
#include <utility>

#include "glad/gl.h"

// #include "GLwrap/Buffer.h"
#include "GLwrap/Vbo.h"
#include "GLwrap/Veo.h"

namespace GLwrap {

struct VAOdata {
    std::shared_ptr<VBO> vbo;

};

class VAO {
public:
    VAO();
    virtual ~VAO();

    using Attr = std::pair<std::shared_ptr<VBO>, std::shared_ptr<VBO::Attrib>>;
    using AttrList = std::vector<Attr>; 
    void load(const AttrList &attrs, std::shared_ptr<VEO> veo);

    void bind();
    void unbind();

    GLuint id();

private:
    GLuint __id;

    std::vector<std::shared_ptr<VBO>> __vbos;
    std::shared_ptr<VEO> __veo;
};

}