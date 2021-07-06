#include "Data/Primitive.h"

// #include <stdexcept>
// #include <algorithm>

// #include "Data/ModelData.h"
// #include "Data/BufferView.h"
#include "Log.h"

using namespace Graphics;

Primitive::Primitive(std::shared_ptr<BufferElementGL> indices,
                     std::unordered_map<int, std::shared_ptr<BufferVertexGL>> attributes,
                     GLwrap::DrawMode mode) :
    _indices(indices),
    _attributes(attributes){
    
    std::unordered_map<int, GLwrap::Array::BufferPair> layouts;
    for (auto iter : attributes){
        auto gl_buffer = iter.second->data;
        auto gl_accessor = std::make_shared<GLwrap::BufferAccessor>(
            static_cast<GLwrap::ComponentSize>(iter.second->data_size),
            static_cast<GLwrap::ComponentType>(iter.second->data_type),
            iter.second->normalized,
            0, 0);
        layouts[iter.first] = std::make_pair(gl_buffer, gl_accessor);
    }

    _vao = std::make_shared<GLwrap::Array>(indices->data, layouts);
    _mode = mode;
}

// Primitive::Primitive(const tinygltf::Primitive &primitive,
//                      ModelData &data){
    
//     using BufferPair = GLwrap::Array::BufferPair;

//     std::unordered_map<int, BufferPair> layouts;
//     for (auto &attr : primitive.attributes){
//         auto &name = attr.first;

//         int loc;
//         try{
//             loc = glTF::getLayoutLocation(name);
//         } catch (std::exception e){
//             LOG(ERR) << "Can not create primitive. " << e.what();
//             continue;
//         }

//         auto accessor = data.getAccessor(attr.second);
//         auto buffer = accessor->view->buffer;

//         // auto 

//         layouts[loc] = std::make_pair(accessor->view->buffer, accessor->accessor);
//     }

//     auto indices_acc = data.getAccessor(primitive.indices);
    
//     _vao = std::make_shared<GLwrap::Array>(indices_acc->view->buffer, layouts);
//     _mode = glTF::getDrawMode(primitive.mode);
//     _type = indices_acc->accessor->component_type;
//     _count = indices_acc->count;
//     _offset = indices_acc->accessor->offset;
// }

Primitive::~Primitive(){

}

void Primitive::draw() const {
    if (material){
        material->apply();
    }
    _vao->draw(_mode, static_cast<GLwrap::ComponentType>(_indices->data_type), _indices->count, 0);
}

void Primitive::draw(){
    if (material){
        material->apply();
    }
    _vao->draw(_mode, static_cast<GLwrap::ComponentType>(_indices->data_type), _indices->count, 0);
}