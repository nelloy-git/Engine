#pragma once

#include <unordered_map>

#include "GLwrap/Array.h"
#include "GLwrap/ArrayAccessor.h"

#include "Data/glTF.h"
#include "Data/Material.h"
#include "Data/DataAccessor.h"
#include "Data/BufferView.h"

namespace Graphics {

class ModelData;

class Primitive {
public:
    Primitive(const tinygltf::Model &model,
              const tinygltf::Primitive &primitive,
              ModelData &data);

    virtual ~Primitive();

    void draw();
    void draw() const;



private:
    std::shared_ptr<GLwrap::BufferAccessor>
    _getAttrAccessor(const std::string &name,
                     const tinygltf::Accessor &info,
                     int &attr_loc);

    std::shared_ptr<GLwrap::ArrayAccessor>
    _getIndicesAccessor(const tinygltf::Accessor &info, int draw_mode);

    std::shared_ptr<GLwrap::Buffer>
    _getBuffer(const tinygltf::Accessor &info, ModelData &data);

    std::shared_ptr<GLwrap::Array> _vao;
    std::shared_ptr<GLwrap::ArrayAccessor> _vao_accessor;

    std::shared_ptr<Material> _material = nullptr;
};

}