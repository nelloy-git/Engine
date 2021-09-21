#pragma once

#include "Graphics/Render/Base/Vertex.hpp"
#include "Graphics/Render/Base/Renderer.hpp"

namespace Graphics::Model::Render {

constexpr Graphics::Render::Base::VertexStruct model_vertex_struct = {
    .POS = GLwrap::ElementStruct::Vec3,
    .NORM = GLwrap::ElementStruct::Vec3,
    .TANG = GLwrap::ElementStruct::Vec4,

    .COLOR_COUNT = 1,
    .COLOR = GLwrap::ElementStruct::Vec4,

    .TEX_COORD_COUNT = 2,
    .TEX_COORD = GLwrap::ElementStruct::Vec2,

    .JOINTS_COUNT = 1,
    .JOINTS = GLwrap::ElementStruct::Vec4,
    .WEIGHTS = GLwrap::ElementStruct::Vec4,

    .MORPH_COUNT = 8,
    .MORPH = GLwrap::ElementStruct::Vec3,

    .CUSTOM_COUNT = 0,
    .CUSTOM = GLwrap::ElementStruct::Vec3
};

using Vertex = Graphics::Render::Base::Vertex<model_vertex_struct>;
using Primitive = Graphics::Render::Base::Primitive<model_vertex_struct>;
using Renderer = Graphics::Render::Base::Renderer<model_vertex_struct>;

const Renderer &getRenderer();
const Primitive::Accessors &getAccessors();
Primitive *createCube();

}