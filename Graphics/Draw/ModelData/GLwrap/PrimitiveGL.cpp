#include "Draw/ModelData/GLwrap/PrimitiveGL.h"

#include "GLwrap/Array.h"
#include "GLwrap/Program.h"

#include "Draw/Types.h"

#include "Draw/ModelData/GLwrap/BufferGL.h"
#include "Draw/ModelData/GLwrap/TypesGL.h"

#include "Log.h"

using namespace Graphics::Draw;

PrimitiveGL::PrimitiveGL(){
}

PrimitiveGL::~PrimitiveGL(){
}

void PrimitiveGL::init(){

    std::unordered_map<int, GLwrap::Array::BufferPair> gl_layouts;

    for (auto &iter : attributes){
        auto attr = iter.first;
        auto buffer = std::dynamic_pointer_cast<BufferGL>(iter.second);
        if (!buffer){
            LOG(ERR) << "got non GLwrap buffer.";
            continue;
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
                continue;
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
            return;
        }

        const auto &data = std::get<BufferGL::GpuData>(ind->data);
        vao = std::make_shared<GLwrap::Array>(*data.gl_data, gl_layouts);
    } else {
        vao = std::make_shared<GLwrap::Array>(gl_layouts);
    }
    
    _inited = true;
}

bool PrimitiveGL::draw() const {
    if (!_inited){
        LOG(WRN) << "must init first.";
        return false;
    }

    if (indices){
        vao->drawElements(toGLwrap(mode), toGLwrap(indices->data_type), indices->count, 0);
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