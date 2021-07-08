#pragma once

#include "GLwrap/Types.h"

#include "Model/Types.h"

namespace Graphics::Model {

constexpr inline GLwrap::BufferType toGLwrap(BufferType type);
constexpr inline GLwrap::ElementType toGLwrap(BufferElemType elem_type);
constexpr inline GLwrap::ElementStruct toGLwrap(BufferElemStruct elem_struct);

constexpr inline GLwrap::Tex2DPixelFormat toGLwrap(TextureFormat fmt);
constexpr inline GLwrap::Tex2DWrap toGLwrap(TextureWrap wrap);
constexpr inline GLwrap::Tex2DFilter toGLwrap(TextureFilter filter);

constexpr inline GLwrap::DrawMode toGLwrap(PrimitiveDrawMode mode);

}