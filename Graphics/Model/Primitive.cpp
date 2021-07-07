#include "Model/Primitive.h"

#include "GLwrap/Array.h"
#include "GLwrap/Program.h"

#include "Log.h"

using namespace Graphics::Model;

constexpr inline GLwrap::ComponentType toGL(BufferElemType elem_type){
    constexpr GLwrap::ComponentType map[] = {
        GLwrap::ComponentType::Byte,
        GLwrap::ComponentType::UByte,
        GLwrap::ComponentType::Short,
        GLwrap::ComponentType::UShort,
        GLwrap::ComponentType::Int,
        GLwrap::ComponentType::UInt,
        GLwrap::ComponentType::Float,
        GLwrap::ComponentType::Double,
    };

    return map[toUint(elem_type)];
}

constexpr inline GLwrap::DrawMode toGL(PrimitiveDrawMode mode){
    constexpr GLwrap::DrawMode map[] = {
        GLwrap::DrawMode::POINTS,
        GLwrap::DrawMode::LINE,
        GLwrap::DrawMode::LINE_LOOP,
        GLwrap::DrawMode::LINE_STRIP,
        GLwrap::DrawMode::TRIANGLES,
        GLwrap::DrawMode::TRIANGLE_STRIP,
        GLwrap::DrawMode::TRIANGLE_FAN,
    };

    return map[toUint(mode)];
}

Primitive::Primitive(){
}

Primitive::~Primitive(){
}

void Primitive::initGL(const GLwrap::Program &prog){

    std::unordered_map<int, GLwrap::Array::BufferPair> gl_layouts;

    for (auto iter : attributes){
        auto name = toString(iter.first);
        auto acc = iter.second->accessor;
        auto buff = iter.second->data;

        auto loc = prog.getAttribLoc(name);
        if (!_verifyLoc(loc, name)){
            continue;
        }

        gl_layouts[loc] = std::make_pair(buff, acc);
    }

    for (int i = 0; i < targets.size(); i++){
        auto targ = targets[i];
        std::string prefix("Target" + std::to_string(i) + "_");

        if (targets[i].pos){
            auto name = prefix + toString(PrimitiveAttribute::Position);
            auto loc = prog.getAttribLoc(name);
            if (_verifyLoc(loc, name)){
                continue;
            }
            gl_layouts[loc] = std::make_pair(targ.pos->data, targ.pos->accessor);
        }

        if (targets[i].norm){
            auto name = prefix + toString(PrimitiveAttribute::Normal);
            auto loc = prog.getAttribLoc(name);
            if (_verifyLoc(loc, name)){
                continue;
            }
            gl_layouts[loc] = std::make_pair(targ.norm->data, targ.norm->accessor);
        }

        if (targets[i].tang){
            auto name = prefix + toString(PrimitiveAttribute::Tangent);
            auto loc = prog.getAttribLoc(name);
            if (_verifyLoc(loc, name)){
                continue;
            }
            gl_layouts[loc] = std::make_pair(targ.tang->data, targ.tang->accessor);
        }
    }

    _inited_prog = &prog;
    _vao = std::make_shared<GLwrap::Array>(indices, attributes);
}

bool Primitive::draw(const GLwrap::Program &prog){
    if (!_vao){
        LOG(WRN) << "was not inited.";
        return false;
    }

    if (_inited_prog != &prog){
        LOG(WRN) << "was inited with other gl program.";
        return false;
    }

    if (indices){
        _vao->drawElements(toGL(mode), toGL(indices->data_type), indices->count, 0);
    }
}

bool Primitive::_verifyLoc(int loc, const std::string &name){
    if (loc < 0){
        LOG(WRN) << "gl program does not have attribute " << name << ". Attribute ignored.";
        return false;
    } else if (loc > GLwrap::Array::max_layouts){
        LOG(WRN) << "OpenGL can not use location " << loc << " for attribute" << name
                 << ". Only " << GLwrap::Array::max_layouts << " are available. Attribute ignored.";
        return false;
    }
    return true;
}