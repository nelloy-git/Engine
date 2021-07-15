#include "Draw/Loader/toGLwrap/ShaderGLwrap.h"

#include <glm/gtc/type_ptr.hpp>

#include "Log.h"

#include "GLwrap/Program.h"
#include "GLwrap/Shader.h"

using namespace Graphics::Draw;

ShaderGLwrap::ShaderGLwrap(const std::string &vertex_source,
                           const std::string &fragment_source) :
    Shader(){

    auto vert = std::make_shared<GLwrap::Shader>(GLwrap::ShaderType::Vertex, vertex_source);
    auto frag = std::make_shared<GLwrap::Shader>(GLwrap::ShaderType::Fragment, fragment_source);
    program = std::make_shared<GLwrap::Program>(std::vector({vert, frag}));
}

ShaderGLwrap::~ShaderGLwrap(){
}

bool ShaderGLwrap::verify(){
    bool verified = true;

    verified == verified && _verifyAttributes();
    verified == verified && _verifyMorphs();
    verified == verified && _verifyUniforms();

    auto log = LOG(MSG);
    for (int i = 0; i < _messages.size(); ++i){
        log << _messages[i] << "\n";
    }

    return verified;
}

void ShaderGLwrap::draw(const Object &obj, const glm::mat4 &camera_mat){
    std::shared_ptr<Model> model = obj.model;
    if (!model){return;}

    auto scene = model->scenes[obj.active_scene];
    for (int i = 0; i < scene->nodes.size(); ++i){
        auto node = scene->nodes[i];
        auto &pose_mat = obj.getMatrix(*node);
        auto parent_mat = camera_mat * pose_mat;
        _drawNode(*scene->nodes[i], obj, camera_mat);
    }
}

void ShaderGLwrap::_drawNode(const Node &node, const Object &obj, const glm::mat4 &parent_mat){
    auto &mat = obj.getMatrix(node);
    program->setUniformMat4f("model", glm::value_ptr(parent_mat * mat));

    if (node.mesh){
        node.mesh->draw();
    }

    for (int i = 0; i < node.children.size(); ++i){
        _drawNode(*node.children[i], obj, parent_mat);
    }
}

bool ShaderGLwrap::_verifyAttributes(){
    bool ok = true;

    constexpr auto attr_count = enumCount<PrimitiveAttribute>();
    _messages.push_back("Attributes:");
    for (int i = 0; i < attr_count; ++i){
        auto attr = magic_enum::enum_value<PrimitiveAttribute>(i);
        auto attr_name = toString(attr);
        auto attr_loc = getLocation(attr);

        bool valid = attr_loc == program->getAttribLoc(attr_name);
        _messages.push_back("\t\"" + attr_name + "\" "
                            + (valid ? "found" : "NOT FOUND"));
        ok &= valid;
    }

    return ok;
}

bool ShaderGLwrap::_verifyMorphs(){
    constexpr PrimitiveAttribute targets[] = {
        PrimitiveAttribute::Position,
        PrimitiveAttribute::Normal,
        PrimitiveAttribute::Tangent
    };

    bool ok = true;
    _messages.push_back("Morph targets:");
    for (int i = 0; i < 4; ++i){
        for (auto targ : targets){
            auto targ_name = getMorphTargetName(i, targ);
            auto targ_loc = getMorphTargetLocation(i, targ);

            bool valid = targ_loc == program->getAttribLoc(targ_name);
            _messages.push_back("\t\"" + targ_name + "\" "
                                + (valid ? "found" : "NOT FOUND"));
            ok &= valid;
        }
    }

    return ok;
}

bool ShaderGLwrap::_verifyUniforms(){
    bool ok = true;
    _messages.push_back("Uniforms:");

    bool valid = (program->getUniformLoc("model") >= 0);
    _messages.push_back("\t\"model\" " + std::string(valid ? "found" : "NOT FOUND"));
    ok &= valid;

    return ok;
}