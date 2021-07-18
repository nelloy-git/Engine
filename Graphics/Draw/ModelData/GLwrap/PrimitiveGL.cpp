#include "Draw/ModelData/GLwrap/PrimitiveGL.hpp"

#include "GLwrap/Array.h"
#include "GLwrap/Program.h"

#include "Draw/Types.h"

#include "Draw/ModelData/GLwrap/BufferGL.hpp"
#include "Draw/ModelData/GLwrap/TypesGL.h"

#include "Log.h"

using namespace Graphics::Draw;

PrimitiveGL::PrimitiveGL(){
}

PrimitiveGL::~PrimitiveGL(){
}

bool PrimitiveGL::init(){
    _inited = false;

    std::unordered_map<int, GLwrap::Array::BufferPair> gl_layouts;

    for (auto &iter : attributes){
        auto attr = iter.first;
        auto buffer = std::dynamic_pointer_cast<BufferGL>(iter.second);
        if (!buffer){
            LOG(ERR) << "got non GLwrap buffer.";
            return false;
        }

        auto loc = getLocation(iter.first);
        if (!_verifyLoc(loc, toString(attr))){
            continue;
        }

        const auto &data = std::get<BufferGL::GpuData>(buffer->data);
        gl_layouts[loc] = std::make_pair(data.gl_data.get(), data.gl_accessor.get());
    }

    for (int i = 0; i < morph_targets.size(); i++){
        auto targ = morph_targets[i];

        PrimitiveAttribute attr_list[] = {
            PrimitiveAttribute::Position,
            PrimitiveAttribute::Normal,
            PrimitiveAttribute::Tangent
        };

        std::shared_ptr<Buffer> buff_list[] = {
            targ.pos,
            targ.norm,
            targ.tang
        };

        for (int j = 0; j < 3; j++){
            auto attr = attr_list[j];
            auto name = getMorphTargetName(i, attr);
            auto loc = getMorphTargetLocation(i, attr);

            auto buffer = std::dynamic_pointer_cast<BufferGL>(buff_list[j]);
            if (!buffer){
                LOG(ERR) << "got non GLwrap buffer. Attribute: " << name;
                return false;
            }

            if (_verifyLoc(loc, name)){
                continue;
            }

            const auto &data = std::get<BufferGL::GpuData>(buffer->data);
            gl_layouts[loc] = std::make_pair(data.gl_data.get(), data.gl_accessor.get());
        }
    }

    if (indices){
        auto ind = std::dynamic_pointer_cast<BufferGL>(indices);
        if (!ind){
            LOG(ERR) << "got non GLwrap buffer.";
            return false;
        }

        const auto &data = std::get<BufferGL::GpuData>(ind->data);
        vao = std::make_shared<GLwrap::Array>(*data.gl_data, gl_layouts);
    } else {
        vao = std::make_shared<GLwrap::Array>(gl_layouts);
    }
    
    _inited = true;
    return true;
}

bool PrimitiveGL::draw() const {
    if (!_inited){
        LOG(WRN) << "must init first.";
        return false;
    }

    if (indices){
        vao->drawElements(toGLwrap(mode), toGLwrap(indices->data_type), indices->count, 0);
    } else {
        auto vert = attributes.find(PrimitiveAttribute::Position);
        if (vert == attributes.end()){
            return false;
        }
        vao->drawArrays(toGLwrap(mode), 0, vert->second->count);
    }

    return true;
}

bool PrimitiveGL::_verifyLoc(int loc, const std::string &name){
    if (loc < 0){
        LOG(WRN) << "gl program does not have attribute " << name << ". Attribute ignored.";
        return false;
    } else if (loc > GLwrap::Array::max_layouts()){
        LOG(WRN) << "OpenGL can not use location " << loc << " for attribute" << name
                 << ". Only " << GLwrap::Array::max_layouts() << " are available. Attribute ignored.";
        return false;
    }
    return true;
}