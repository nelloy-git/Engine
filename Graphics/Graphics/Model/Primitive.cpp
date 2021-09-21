#include "Graphics/Model/Primitive.h"

#include "tiny_gltf.h"

#include "Graphics/Model/TypesGltf.h"

using namespace Graphics::Model;


Primitive::Primitive(const tinygltf::Model &model,
                     const tinygltf::Primitive &primitive){
    



}


void Primitive::_loadIndices(const tinygltf::Model &model,
                             const tinygltf::Accessor &accessor,
                             std::vector<unsigned int> &dst){
    auto &view = model.bufferViews[accessor.bufferView];
    auto &buffer = model.buffers[view.buffer];

    auto elem_type = gltf::toElemType(accessor.componentType);
    if (!(elem_type == GLwrap::ElementType::UByte
          || elem_type == GLwrap::ElementType::UShort
          || elem_type == GLwrap::ElementType::UInt)){
        
        throw std::runtime_error("Got invalid indices componentType.");
    }

    auto elem_struct = gltf::toElemStruct(accessor.type);
    if (elem_struct != GLwrap::ElementStruct::Scalar){
        throw std::runtime_error("Got invalid indices componentStruct.");
    }
    size_t elem_bytes = getSize(elem_type) * getCount(elem_struct);

    size_t step_bytes = view.byteStride == 0 ? elem_bytes : view.byteStride;

    dst.resize(accessor.count);
    for (int i = 0; i < accessor.count; ++i){
        auto addr = view.byteOffset + accessor.byteOffset + i * step_bytes;

        if (elem_type == GLwrap::ElementType::UByte){
            unsigned char val;
            memcpy(&val, &buffer.data.at(addr), sizeof(val));
            dst[i] = val;
        } else if (elem_type == GLwrap::ElementType::UShort){
            unsigned short int val;
            memcpy(&val, &buffer.data.at(addr), sizeof(val));
            dst[i] = val;
        } else {
            unsigned int val;
            memcpy(&val, &buffer.data.at(addr), sizeof(val));
            dst[i] = val;
        }
    }
}