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
    void draw(const Object &obj, const glm::mat4 &camera_mat) override;

    std::shared_ptr<GLwrap::Program> program;

private:
    bool _verifyAttributes();
    bool _verifyMorphs();
    bool _verifyUniforms();

    void _drawNode(const Node &node, const Object &obj, const glm::mat4 &parent_mat);

    std::vector<std::string> _messages;
};

}