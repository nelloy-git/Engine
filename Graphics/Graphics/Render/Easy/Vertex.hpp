#pragma once

#include "GLwrap/Vertex.hpp"

namespace Graphics::Render::Easy {

using VertAttrib = glw::VertAttrib;
using DataType = glw::gpu_data_type;

// constexpr VertAttrib POS {VertAttrib::Count::_3, DataType::Float, false};
// constexpr VertAttrib NOR {VertAttrib::Count::_4, DataType::Int_2_10_10_10, true};
// constexpr VertAttrib TAN {VertAttrib::Count::_4, DataType::Int_2_10_10_10, true};

// class Vertex : public GLwrap::Vertex<POS, NOR, TAN> {
// public:
//     // Position
//     inline void setPosX(float x){get<0>()[0] = x;};
//     inline void setPosY(float y){get<0>()[1] = y;};
//     inline void setPosZ(float z){get<0>()[2] = z;};

//     // Normal
//     inline void setNormX(float x){_setInt_2_10_10_10_X(get<1>()[0], x);};
//     inline void setNormY(float y){_setInt_2_10_10_10_Y(get<1>()[0], y);};
//     inline void setNormZ(float z){_setInt_2_10_10_10_Z(get<1>()[0], z);};
//     inline void setNormW(float w){_setInt_2_10_10_10_W(get<1>()[0], w);};

//     // Tangent
//     inline void setTangX(float x){_setInt_2_10_10_10_X(get<2>()[0], x);};
//     inline void setTangY(float y){_setInt_2_10_10_10_Y(get<2>()[0], y);};
//     inline void setTangZ(float z){_setInt_2_10_10_10_Z(get<2>()[0], z);};
//     inline void setTangW(float w){_setInt_2_10_10_10_W(get<2>()[0], w);};

// private:
//     static inline void _setInt_2_10_10_10_X(uint32_t &dst, float x){
//         const uint32_t xs = x < 0 ? 1 : 0;
//         dst = dst | xs << 9 | ((uint32_t)(x * 511 + (xs << 9)) & 511);
//     }

//     static inline void _setInt_2_10_10_10_Y(uint32_t &dst, float y){
//         const uint32_t ys = y < 0 ? 1 : 0;
//         dst = dst | ys << 19 | (((uint32_t)(y * 511 + (ys << 9)) & 511) << 10);
//     }

//     static inline void _setInt_2_10_10_10_Z(uint32_t &dst, float z){
//         const uint32_t zs = z < 0 ? 1 : 0;
//         dst = dst | zs << 29 | (((uint32_t)(z * 511 + (zs << 9)) & 511) << 20);
//     }

//     static inline void _setInt_2_10_10_10_W(uint32_t &dst, float w){
//         const uint32_t ws = w < 0 ? 1 : 0;
//         dst = dst | ws << 31 | (((uint32_t)(w + (ws << 1)) & 1) << 30);
//     }

// };

}


// constexpr Graphics::Render::Base::VertexStruct VERT_STRUCT = {
//     .POS = {Base::ElemSize::Vec3, Base::ElemType::Float, false, sizeof(Base::Vertex<VERT_STRUCT>), 0},
//     .NOR = {Base::ElemSize::Vec4, Base::ElemType::Int_2_10_10_10, true, sizeof(Base::Vertex<VERT_STRUCT>), 0},
//     .TAN = {Base::ElemSize::Vec4, Base::ElemType::Int_2_10_10_10, true, sizeof(Base::Vertex<VERT_STRUCT>), 0},

//     .COL_N = 1,
//     .COL = {Base::ElemSize::Vec4, Base::ElemType::Byte, true, sizeof(Base::Vertex<VERT_STRUCT>), 0},

//     .TEX_N = 2,
//     .TEX = {Base::ElemSize::Vec2, Base::ElemType::Byte, true, sizeof(Base::Vertex<VERT_STRUCT>), 0},

//     .JNT_N = 2,
//     .JNT = {Base::ElemSize::Vec4, Base::ElemType::Float, false, sizeof(Base::Vertex<VERT_STRUCT>), 0},
    

//     // .NORM = GLwrap::ElementStruct::Vec3,
//     // .TANG = GLwrap::ElementStruct::Vec4,

//     // .COLOR_COUNT = 1,
//     // .COLOR = GLwrap::ElementStruct::Vec4,

//     // .TEX_COORD_COUNT = 2,
//     // .TEX_COORD = GLwrap::ElementStruct::Vec2,

//     // .JOINTS_COUNT = 1,
//     // .JOINTS = GLwrap::ElementStruct::Vec4,
//     // .WEIGHTS = GLwrap::ElementStruct::Vec4,

//     // .MORPH_COUNT = 8,
//     // .MORPH = GLwrap::ElementStruct::Vec3,

//     // .CUSTOM_COUNT = 0,
//     // .CUSTOM = GLwrap::ElementStruct::Vec3
// };

// typedef Graphics::Render::Base::Vertex<VERT_STRUCT> Vertex;
// typedef Graphics::Render::Base::Primitive<VERT_STRUCT> Primitive;
