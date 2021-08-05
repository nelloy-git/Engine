#include "Draw/ShaderGL.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include "glm/gtc/type_ptr.hpp"

#include "Log.h"

#include "GLwrap/Program.h"
#include "GLwrap/Shader.h"

#include "Draw/ModelData/GLwrap/PrimitiveGL.hpp"
#include "Draw/ModelData/GLwrap/TextureGL.hpp"

using namespace Graphics::Draw;

ShaderGL::ShaderGL(const std::string &vertex_source,
                   const std::string &fragment_source) :
    Shader(){

    auto vert = std::make_shared<GLwrap::Shader>(GLwrap::ShaderType::Vertex, vertex_source);
    auto frag = std::make_shared<GLwrap::Shader>(GLwrap::ShaderType::Fragment, fragment_source);
    program = std::make_shared<GLwrap::Program>(std::vector({vert, frag}));
    program->use();
}

ShaderGL::~ShaderGL(){
}

std::shared_ptr<ShaderGL> ShaderGL::fromFiles(const std::string &vertex_path,
                                              const std::string &fragment_path){
    auto vert = _readFile(vertex_path);
    auto frag = _readFile(fragment_path);
    return std::make_shared<ShaderGL>(vert, frag);
};

std::string ShaderGL::_readFile(const std::string &path){
    std::string code;
    std::ifstream file;

    // ensure ifstream objects can throw exceptions:
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        file.open(path);
        std::stringstream str_stream;

        std::string line;
        while(!file.eof()){
	        std::getline(file, line); // Saves the line in STRING.
	        code += line + "\n"; 
        }
        file.close();
    } catch(std::ifstream::failure e){
        LOG(WRN) << "can not read file";
    }

    return code;
}

bool ShaderGL::verify(){
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

void ShaderGL::draw(const Object &obj){

    std::shared_ptr<Model> model = obj.getModel();
    if (!model){
        return;
    }

    int scene_index = obj.getScene();
    if (scene_index < 0){
        return;
    }

    auto scene = model->scenes()[scene_index];
    for (int i = 0; i < scene->nodes.size(); ++i){
        auto node = scene->nodes[i];
        _drawNode(*node, obj);
    }
}

void ShaderGL::_drawNode(const Node &node, const Object &obj){
    auto mat = obj.getNodeMat(node.index);

    auto mesh = node.mesh;
    if (mesh && mat != nullptr){
        program->setUniformMat4f("model", glm::value_ptr(*mat));
        program->setUniform1vi("morph_targets", mesh->weights.size());
        for (int i = 0; i < mesh->weights.size(); ++i){
            program->setUniform1vf("morph_weights[" + std::to_string(i) + "]", mesh->weights[i]);
        }

        for (int i = 0; i < mesh->primitives().size(); ++i){
            auto prim = mesh->primitives()[i];
            if (!prim){
                continue;
            }

            int morph_attr_count = 0;
            if (prim->morph_targets.size() > 0){
                auto targ = prim->morph_targets[0];
                if (targ.pos){++morph_attr_count;}
                if (targ.norm){++morph_attr_count;}
                if (targ.tang){++morph_attr_count;}
            }

            program->setUniform1vi("morph_attributes", morph_attr_count);
            auto prim_gl = std::dynamic_pointer_cast<PrimitiveGL>(prim);
            if (prim_gl){
                _applyMaterial(*prim_gl->material);
                prim_gl->draw();
            }
        }
    }
#ifdef DEBUG
    else if (mat == nullptr) {
        LOG(MSG) << node.index << " empty mat.";
    }
#endif

    for (int i = 0; i < node.children.size(); ++i){
        _drawNode(*node.children[i], obj);
    }
}

void ShaderGL::_applyMaterial(const Material &mater){
    program->setUniformVec4f("baseColor", glm::value_ptr(mater.base_color));
    auto tex = std::dynamic_pointer_cast<TextureGL>(mater.base_texture);
    tex->setActive(0);
}

bool ShaderGL::_verifyAttributes(){
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

bool ShaderGL::_verifyMorphs(){
    constexpr PrimitiveAttribute targets[] = {
        PrimitiveAttribute::Position,
        PrimitiveAttribute::Normal,
        PrimitiveAttribute::Tangent
    };

    bool ok = true;
    // _messages.push_back("Morph targets:");
    // for (int i = 0; i < 4; ++i){
    //     for (auto targ : targets){
    //         auto targ_name = getMorphTargetName(i, targ);
    //         auto targ_loc = getMorphTargetLocation(i, targ);

    //         bool valid = targ_loc == program->getAttribLoc(targ_name);
    //         _messages.push_back("\t\"" + targ_name + "\" "
    //                             + (valid ? "found" : "NOT FOUND"));
    //         ok &= valid;
    //     }
    // }

    return ok;
}

bool ShaderGL::_verifyUniforms(){
    bool ok = true;
    _messages.push_back("Uniforms:");

    bool valid = (program->getUniformLoc("model") >= 0);
    _messages.push_back("\t\"model\" " + std::string(valid ? "found" : "NOT FOUND"));
    ok &= valid;

    return ok;
}