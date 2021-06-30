#pragma once

#include <unordered_map>

#include "GLwrap/Array.h"

#include "Data/glTF.h"
#include "Data/Material.h"
#include "Data/Accessor.h"
#include "Data/BufferView.h"

namespace Graphics {

class ModelData;

class Primitive {
public:
    Primitive(const tinygltf::Primitive &primitive,
              ModelData &data);

    virtual ~Primitive();

    void draw();
    void draw() const;



private:

    std::shared_ptr<GLwrap::Array> _vao;
    GLwrap::DrawMode _mode;
    GLwrap::ComponentType _type;
    int _count;
    size_t _offset;

    std::shared_ptr<Material> _material = nullptr;
};

}