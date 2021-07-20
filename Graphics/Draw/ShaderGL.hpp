#pragma once

#include "Draw/Shader.h"

namespace GLwrap {
    class Program;
};

namespace Graphics::Draw {

class ShaderGL : public Shader {
public:
    ShaderGL(const std::string &vertex_source,
             const std::string &fragment_source);
    virtual ~ShaderGL();

    static std::shared_ptr<ShaderGL> fromFiles(const std::string &vertex_path,
                                               const std::string &fragment_path);

    bool verify() override;
    void draw(const Object &obj) override;

    std::shared_ptr<GLwrap::Program> program;

private:
    bool _verifyAttributes();
    bool _verifyMorphs();
    bool _verifyUniforms();

    void _drawNode(const Node &node, const Object &obj);
    void _applyMaterial(const Material &material);

    std::vector<std::string> _messages;

    static std::string _readFile(const std::string &path);
};

}