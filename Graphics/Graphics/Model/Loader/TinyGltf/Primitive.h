#pragma once

#include <vector>
#include <experimental/source_location>
using SrcLoc = std::experimental::source_location;

#include "Graphics/Render/Base/Vertex.hpp"

#include "Graphics/Model/Loader/TinyGltf/Utils.h"

namespace Graphics::Model::gltf {

std::unique_ptr<std::vector<unsigned int>> loadIndices(const tinygltf::Model &model,
                                                       const tinygltf::Accessor &accessor){
    auto dst = std::make_unique<std::vector<unsigned int>>(accessor.count);

    auto elem_type = gltf::toElemType(accessor.componentType);
    auto elem_struct = gltf::toElemStruct(accessor.type);

    if (elem_struct != GLwrap::ElementStruct::Scalar){
        detailed::throwErr("Got invalid indices componentStruct.");
    }

    auto dst_ptr = reinterpret_cast<char *>(dst->data());
    switch (elem_type){
    case GLwrap::ElementType::UByte:
        detailed::loadAccessor<unsigned int, unsigned char>(model, accessor, dst_ptr, 0, sizeof(unsigned int));
        break;
        
    case GLwrap::ElementType::UShort:
        detailed::loadAccessor<unsigned int, unsigned short int>(model, accessor, dst_ptr, 0, sizeof(unsigned int));
        break;
        
    case GLwrap::ElementType::UInt:
        detailed::loadAccessor<unsigned int, unsigned int>(model, accessor, dst_ptr, 0, sizeof(unsigned int));
        break;
    
    default:
        detailed::throwErr("Got invalid indices componentType.");
    }

    return dst;
}

using VertexStruct = Render::Base::VertexStruct;
template<VertexStruct S>
using Vertex = Render::Base::Vertex<S>;

template<class R, class Out, class In>
constexpr R min(const Out &v1, const In &v2){
    return v1 > v2 ? v2 : v1;
}

template<VertexStruct S>
inline void loadPosition(const tinygltf::Model &model,
                         const tinygltf::Accessor &accessor,
                         std::vector<Vertex<S>> &dst){
    auto dst_ptr = reinterpret_cast<char *>(dst.data());
    detailed::loadVecNormalized<3>(model, accessor, dst_ptr, offsetof(Vertex<S>, pos), sizeof(Vertex<S>));
};

// void loadNormal(const tinygltf::Model &model,
//                 const tinygltf::Accessor &accessor,
//                 std::vector<Render::Vertex> &dst);

// void loadTangent(const tinygltf::Model &model,
//                  const tinygltf::Accessor &accessor,
//                  std::vector<Render::Vertex> &dst);

// void loadTex0(const tinygltf::Model &model,
//               const tinygltf::Accessor &accessor,
//               std::vector<Render::Vertex> &dst);

// void loadTex1(const tinygltf::Model &model,
//               const tinygltf::Accessor &accessor,
//               std::vector<Render::Vertex> &dst);

// void loadColor(const tinygltf::Model &model,
//                const tinygltf::Accessor &accessor,
//                std::vector<Render::Vertex> &dst);

// void loadJoints(const tinygltf::Model &model,
//                 const tinygltf::Accessor &accessor,
//                 std::vector<Render::Vertex> &dst);
                
// void loadWeights(const tinygltf::Model &model,
//                  const tinygltf::Accessor &accessor,
//                  std::vector<Render::Vertex> &dst);
                
// void loadMorph(const tinygltf::Model &model,
//                const tinygltf::Accessor &accessor,
//                size_t n,
//                std::vector<Render::Vertex> &dst);

}