#pragma once

#include "glw/Object.hpp"

namespace Graphics::Render::Base {

using Pos =  glw::Attribute<glw::AttributeMeta<glw::gpu_data_type::GLfloat, 3, false>>;
using Norm = glw::Attribute<glw::AttributeMeta<glw::gpu_data_type::GLint_2_10_10_10, 4, true>>;
using Tang = glw::Attribute<glw::AttributeMeta<glw::gpu_data_type::GLint_2_10_10_10, 4, true>>;
using Col =  glw::Attribute<glw::AttributeMeta<glw::gpu_data_type::GLubyte, 4, true>>;
using Tex =  glw::Attribute<glw::AttributeMeta<glw::gpu_data_type::GLushort, 4, true>>;

using Vertex = glw::Vertex<Pos, Norm, Tang, Col, Tex>;

}