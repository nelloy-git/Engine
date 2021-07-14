#pragma once

#include "Draw/Shader.h"

namespace GLwrap {
    class Program;
};

namespace Graphics::Draw {

class ShaderGLwrap : public Shader {
public:
    ShaderGLwrap(const std::string &vertex_source,
                 const std::string &fragment_source);
    virtual ~ShaderGLwrap();

    bool verify() override;
    void draw(const Object &obj) override;

    std::shared_ptr<GLwrap::Program> program;

private:
    bool _verifyAttributes();
    bool _verifyMorphs();
    bool _verifyUniforms();

    std::vector<std::string> _messages;
};

}