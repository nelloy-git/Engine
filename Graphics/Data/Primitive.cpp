#include "Data/Primitive.h"

#include <stdexcept>
#include <algorithm>

#include "Data/ModelData.h"
#include "Data/BufferView.h"
#include "Log.h"

using namespace Graphics;

Primitive::Primitive(const tinygltf::Primitive &primitive,
                     ModelData &data){
    
    using BufferPair = GLwrap::Array::BufferPair;

    std::unordered_map<int, BufferPair> layouts;
    for (auto &attr : primitive.attributes){
        auto &name = attr.first;

        int loc;
        try{
            loc = glTF::getLayoutLocation(name);
        } catch (std::exception e){
            LOG(ERR) << "Can not create primitive. " << e.what();
            continue;
        }

        auto accessor = data.getAccessor(attr.second);
        auto buffer = accessor->view->buffer;

        // auto 

        layouts[loc] = std::make_pair(accessor->view->buffer, accessor->accessor);
    }

    auto indices_acc = data.getAccessor(primitive.indices);
    
    _vao = std::make_shared<GLwrap::Array>(indices_acc->view->buffer, layouts);
    _mode = glTF::getDrawMode(primitive.mode);
    _type = indices_acc->accessor->component_type;
    _count = indices_acc->count;
    _offset = indices_acc->accessor->offset;
}

Primitive::~Primitive(){

}

void Primitive::draw() const {
    if (_material){
        _material->apply();
    }
    _vao->draw(_mode, _type, _count, _offset);
}

void Primitive::draw(){
    if (_material){
        _material->apply();
    }
    _vao->draw(_mode, _type, _count, _offset);
}