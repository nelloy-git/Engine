#include "Graphics/Model/gltf/Primitive.h"

// #include <experimental/source_location>
// using SrcLoc = std::experimental::source_location;

// #include "Graphics/Model/gltf/Utils.h"
// #include "Graphics/Model/gltf/Types.h"

// using namespace Graphics::Model;

// using Vertex = Graphics::Model::Render::Vertex;


// static inline void throwErr(const std::string &msg, SrcLoc loc = SrcLoc::current()){
//     throw std::runtime_error(std::string(loc.file_name()) + ":"
//                              + std::to_string(loc.line()) + " - "
//                              + msg);
// }

// void gltf::loadIndices(const tinygltf::Model &model,
//                        const tinygltf::Accessor &accessor,
//                        std::vector<unsigned int> &dst){
//     auto elem_type = gltf::toElemType(accessor.componentType);
//     auto elem_struct = gltf::toElemStruct(accessor.type);

//     if (elem_struct != GLwrap::ElementStruct::Scalar){
//         throwErr("Got invalid indices componentStruct.");
//     }

//     switch (elem_type){
//     case GLwrap::ElementType::UByte:
//         gltf::loadAccessor<unsigned int, unsigned char>(model, accessor, dst);
//         break;
        
//     case GLwrap::ElementType::UShort:
//         gltf::loadAccessor<unsigned int, unsigned short int>(model, accessor, dst);
//         break;
        
//     case GLwrap::ElementType::UInt:
//         gltf::loadAccessor<unsigned int, unsigned int>(model, accessor, dst);
//         break;
    
//     default:
//         throwErr("Got invalid indices componentType.");
//     }
// }

// template<class T, size_t S>
// static void loadVecNormalizedBase(const tinygltf::Model &model,
//                                   const tinygltf::Accessor &accessor,
//                                   size_t dst_offset, std::function<float(T)> norm,
//                                   std::vector<Vertex> &dst){
//     using VecT = gltf::vec<T, S>;

//     std::vector<VecT> data;                                       
//     gltf::loadAccessor<VecT, VecT>(model, accessor, data);

//     float normalized[S];
//     for (int i = 0; i < dst.size(); ++i){
//         for (int j = 0; j < S; ++j){
//             normalized[j] = norm(data[i].data[j]);
//         }

//         unsigned char* bytePtr = reinterpret_cast<unsigned char*>(dst.data());
//         bytePtr += dst_offset;

//         memcpy(bytePtr, &normalized, sizeof(normalized));
//     }
// }

// template<size_t S>
// static void loadVecNormalized(const tinygltf::Model &model,
//                               const tinygltf::Accessor &accessor,
//                               size_t dst_offset,
//                               std::vector<Vertex> &dst){
//     auto elem_type = gltf::toElemType(accessor.componentType);
//     auto elem_struct = gltf::toElemStruct(accessor.type);

//     if (GLwrap::getSize(elem_struct) != S){
//         throwErr("Got invalid componentStruct.");
//     }
    
//     static auto norm_ubyte = [](unsigned char v){return v / 255.0;};
//     static auto norm_byte = [](char v){return std::max(v / 127.0, -1.0);};
//     static auto norm_ushort = [](unsigned short int v){return v / 65535.0;};
//     static auto norm_short = [](short int v){return std::max(v / 32767.0, -1.0);};
//     static auto norm_float = [](float v){return v;};
    
//     switch (elem_type){
//     case GLwrap::ElementType::UByte:
//         loadVecNormalizedBase<unsigned char, S>(model, accessor, dst_offset, norm_ubyte, dst);
//         break;
        
//     case GLwrap::ElementType::Byte:
//         loadVecNormalizedBase<char, S>(model, accessor, dst_offset, norm_byte, dst);
//         break;

//     case GLwrap::ElementType::UShort:
//         loadVecNormalizedBase<unsigned short int, S>(model, accessor, dst_offset, norm_ushort, dst);
//         break;

//     case GLwrap::ElementType::Short:
//         loadVecNormalizedBase<short int, S>(model, accessor, dst_offset, norm_short, dst);
//         break;

//     case GLwrap::ElementType::Float:
//         loadVecNormalizedBase<float, S>(model, accessor, dst_offset, norm_ushort, dst);
//         break;
    
//     default:
//         throwErr("Got invalid indices componentType.");
//     }
// }

// void gltf::loadPosition(const tinygltf::Model &model,
//                         const tinygltf::Accessor &accessor,
//                         std::vector<Vertex> &dst){
//     loadVecNormalized<3>(model, accessor, offsetof(Vertex, pos), dst);
// }

// void gltf::loadNormal(const tinygltf::Model &model,
//                       const tinygltf::Accessor &accessor,
//                       std::vector<Vertex> &dst){
//     loadVecNormalized<3>(model, accessor, offsetof(Vertex, norm), dst);
// }

// void gltf::loadTangent(const tinygltf::Model &model,
//                        const tinygltf::Accessor &accessor,
//                        std::vector<Vertex> &dst){
//     loadVecNormalized<4>(model, accessor, offsetof(Vertex, tang), dst);
// }

// void gltf::loadTex0(const tinygltf::Model &model,
//                     const tinygltf::Accessor &accessor,
//                     std::vector<Vertex> &dst){
//     loadVecNormalized<2>(model, accessor, offsetof(Vertex, tex_coord), dst);
// }

// void gltf::loadTex1(const tinygltf::Model &model,
//                     const tinygltf::Accessor &accessor,
//                     std::vector<Vertex> &dst){
//     loadVecNormalized<2>(model, accessor, offsetof(Vertex, tex_coord) + sizeof(Vertex::tex_coord[0]), dst);
// }

// void gltf::loadColor(const tinygltf::Model &model,
//                      const tinygltf::Accessor &accessor,
//                      std::vector<Vertex> &dst){
//     if (gltf::toElemStruct(accessor.type) == GLwrap::ElementStruct::Vec3){
//         loadVecNormalized<3>(model, accessor, offsetof(Vertex, color), dst);
//     } else {
//         loadVecNormalized<4>(model, accessor, offsetof(Vertex, color), dst);
//     }
// }

// void gltf::loadJoints(const tinygltf::Model &model,
//                       const tinygltf::Accessor &accessor,
//                       std::vector<Vertex> &dst){
//     loadVecNormalized<4>(model, accessor, offsetof(Vertex, joints), dst);
// }
                
// void gltf::loadWeights(const tinygltf::Model &model,
//                        const tinygltf::Accessor &accessor,
//                        std::vector<Vertex> &dst){
//     loadVecNormalized<4>(model, accessor, offsetof(Vertex, weights), dst);
// }
                
// void gltf::loadMorph(const tinygltf::Model &model,
//                      const tinygltf::Accessor &accessor,
//                      size_t n,
//                      std::vector<Vertex> &dst){
//     loadVecNormalized<3>(model, accessor, offsetof(Vertex, morph[n]), dst);

// }