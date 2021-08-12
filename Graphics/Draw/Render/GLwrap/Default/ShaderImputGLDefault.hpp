#pragma once

#include "Draw/Render/GLwrap/ShaderInputGL.hpp"

namespace Graphics::Render {

struct ShaderInputGLDefaultInput {
    float pos[3];
    float norm[3];
    float tang[3];
    float color[3];
    float tex_coord_0[2];
    float tex_coord_1[2];
    float joints_0[4];
    float joints_1[4];
    float weights_0[4];
    float weights_1[4];

    float morph_0[3];
    float morph_1[3];
    float morph_2[3];
    float morph_3[3];
    float morph_4[3];
    float morph_5[3];
    float morph_6[3];
    float morph_7[3];
};

class ShaderInputGLDefault : public ShaderInputGL<ShaderInputGLDefaultInput> {
public:
    ShaderInputGLDefault();
    virtual ~ShaderInputGLDefault();

    static virtual const std::vector<const GLwrap::BufferAccessor> &getAccessors();
    
};

}