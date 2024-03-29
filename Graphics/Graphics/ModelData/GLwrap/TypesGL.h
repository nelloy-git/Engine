#pragma once

#include "GLwrap/Types.h"

#include "Graphics/Types.h"

namespace Graphics::Draw {

GLwrap::BufferType toGLwrap(BufferType type);
GLwrap::Type toGLwrap(BufferElemType elem_type);
GLwrap::Size toGLwrap(BufferElemStruct elem_struct);

GLwrap::Tex2DPixelFormat toGLwrap(TextureFormat fmt);
GLwrap::Tex2DWrap toGLwrap(TextureWrap wrap);
GLwrap::Tex2DFilter toGLwrap(TextureFilter filter);

GLwrap::DrawMode toGLwrap(PrimitiveDrawMode mode);

}