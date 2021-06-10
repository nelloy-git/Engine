#pragma once

#include <map>
#include <memory>
#include <stdexcept>

#include "tiny_gltf.h"

#include "GLwrap/Buffer.h"
#include "GLwrap/BufferAttribute.h"
#include "GLwrap/Vao.h"

namespace Graphics {

// vertices     layout = 0
// normals      layout = 1
class Primitive_glTF {
public:
    Primitive_glTF(const tinygltf::Model &model,
                   const tinygltf::Primitive &primitive);
    virtual ~Primitive_glTF();

    void draw();

    // int vertices_count(){return __vertices_count;};

    // const int layout_vertice = 0;
    // const int layout_normal = 1;
    // const int layout_uv = 2;

private:
    int __vertices;
    GLwrap::VAOdrawMode __draw_mode;
    GLwrap::ShaderDataType __indices_type;
    size_t __indices_offset;

    void __loadAttributes(const tinygltf::Model &model, const tinygltf::Primitive &mesh);
    void __loadElements(const tinygltf::Model &model, const tinygltf::Primitive &mesh);
    void __loadVAO();

    std::vector<std::shared_ptr<GLwrap::BufferAttrubute>> __attributes;
    std::shared_ptr<GLwrap::VEO> __veo = nullptr;
    std::shared_ptr<GLwrap::VAO> __vao = nullptr;
};

}