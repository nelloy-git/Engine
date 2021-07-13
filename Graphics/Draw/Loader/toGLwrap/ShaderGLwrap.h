#pragma once

#include "Draw/Shader.h"

namespace Graphics::Draw {

class ShaderGLwrap : public Shader {
public:
    ShaderGLwrap();
    virtual ~ShaderGLwrap();

    bool verify() override;
    void draw(const Object &obj) override;

private:
};

}