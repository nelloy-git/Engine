#pragma once

#include "Graphics/Render/Base/Primitive.hpp"

namespace Graphics::Render::Easy {

constexpr Graphics::Render::Base::VertexStruct VERT_STRUCT = {
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

typedef Graphics::Render::Base::Vertex<VERT_STRUCT> Vertex;
typedef Graphics::Render::Base::Primitive<VERT_STRUCT> Primitive;

}