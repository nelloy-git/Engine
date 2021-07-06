#pragma once

#include <unordered_map>

#include "GLwrap/Array.h"
#include "GLwrap/BufferAccessor.h"

#include "Data/Buffer/BufferElementGL.h"
#include "Data/Buffer/BufferVertexGL.h"
#include "Data/Material.h"

namespace Graphics {



class Primitive {
public:
    Primitive(std::shared_ptr<BufferElementGL> indices,
              std::unordered_map<int, std::shared_ptr<BufferVertexGL>> attributes,
              GLwrap::DrawMode mode);

    virtual ~Primitive();

    void draw();
    void draw() const;

    std::shared_ptr<Material> material = nullptr;

private:

    std::shared_ptr<GLwrap::Array> _vao;
    GLwrap::DrawMode _mode;

    std::shared_ptr<BufferElementGL> _indices;
    std::unordered_map<int, std::shared_ptr<BufferVertexGL>> _attributes;
};

}