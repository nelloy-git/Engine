#include "Model/GLwrap/PrimitiveGLwrap.h"

#include "GLwrap/Array.h"
#include "GLwrap/Program.h"

#include "Model/Types.h"

#include "Model/GLwrap/BufferGLwrap.h"
#include "Model/GLwrap/TypesGLwrap.h"

#include "Log.h"

using namespace Graphics::Model;

PrimitiveGLwrap::PrimitiveGLwrap(){
}

PrimitiveGLwrap::~PrimitiveGLwrap(){
}

void PrimitiveGLwrap::update(){

    std::unordered_map<int, GLwrap::Array::BufferPair> gl_layouts;

    for (auto &iter : attributes){
        auto attr = iter.first;
        auto buffer = std::dynamic_pointer_cast<BufferGLwrap>(iter.second);
        if (!buffer){
            LOG(ERR) << "got non GLwrap buffer.";
            continue;
        }

        auto loc = getLocation(iter.first);
        if (!_verifyLoc(loc, toString(attr))){
            continue;
        }

        gl_layouts[loc] = std::make_pair(buffer->data, buffer->accessor);
    }

    for (int i = 0; i < targets.size(); i++){
        auto targ = targets[i];
        std::string prefix("Target" + std::to_string(i) + "_");

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
            auto name = prefix + toString(attr);
            auto loc = getMorphTargetLocation(i, attr);

            auto buffer = std::dynamic_pointer_cast<BufferGLwrap>(buff_list[j]);
            if (!buffer){
                LOG(ERR) << "got non GLwrap buffer.";
                continue;
            }

            if (_verifyLoc(loc, name)){
                continue;
            }
            gl_layouts[loc] = std::make_pair(buffer->data, buffer->accessor);
        }
    }

    // vao = std::make_shared<GLwrap::Array>()
    if (indices){
        auto buffer = std::dynamic_pointer_cast<BufferGLwrap>(indices);
        if (!buffer){
            LOG(ERR) << "got non GLwrap buffer.";
            return;
        }

        vao = std::make_shared<GLwrap::Array>(*buffer->data, gl_layouts);
    } else {
        vao = std::make_shared<GLwrap::Array>(gl_layouts);
    }
    
}

bool PrimitiveGLwrap::draw(){
    if (!vao){
        LOG(WRN) << "was not inited.";
        return false;
    }

    if (material){
        material->apply();
    }

    if (indices){
        vao->drawElements(toGLwrap(mode), toGLwrap(indices->data_type), indices->count, 0);
    }
}

bool PrimitiveGLwrap::_verifyLoc(int loc, const std::string &name){
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