#pragma once

#include <functional>
#include <variant>
#include <vector>
#include <experimental/source_location>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "tiny_gltf.h"

#include "Graphics/Model/Loader/TinyGltf/Types.h"

namespace Graphics::Model::gltf::detailed {

using SrcLoc = std::experimental::source_location;
    
template<class T, size_t S>
struct vec {
    T data[S];
};

static inline void throwErr(const std::string &msg, SrcLoc loc = SrcLoc::current()){
    throw std::runtime_error(std::string(loc.file_name()) + ":"
                             + std::to_string(loc.line()) + " - "
                             + msg);
}

template<class In, class Out>
void extractData(const char *src, size_t src_offset, size_t src_step,
                 char *dst, size_t dst_offset, size_t dst_step,
                 size_t count, std::function<Out(const In&)> *convert = nullptr){
    char *src_addr = const_cast<char *>(src) + src_offset;
    char *dst_addr = dst + dst_offset;
    
    for (int i = 0; i < count; ++i){
        In *in = reinterpret_cast<In *>(src_addr);
        Out *out = reinterpret_cast<Out *>(dst_addr);
        *out = convert ? (*convert)(*in) : (*reinterpret_cast<Out *>(in));

        src_addr += src_step;
        dst_addr += dst_step;
    }
};

// template<class Out, class In>
// void loadBufferView(const tinygltf::Model &model,
//                     const tinygltf::BufferView &view,
//                     const size_t count, const size_t offset,
//                     std::vector<Out> &dst){
//     auto &buffer = model.buffers[view.buffer];
//     auto step = view.byteStride != 0 ? view.byteStride : sizeof(In);



//     // loadBuffer<Out, In>(buffer, count,
//     //                    view.byteOffset + offset, step,
//     //                    dst);
// };

template<class In, class Out>
void loadAccessor(const tinygltf::Model &model,
                  const tinygltf::Accessor &accessor,
                  char *dst, size_t dst_offset, size_t dst_step,
                  std::function<Out(const In&)> *convert = nullptr){
    auto &view = model.bufferViews[accessor.bufferView];

    const char *src = reinterpret_cast<const char *>(model.buffers[view.buffer].data.data());
    size_t src_offset = view.byteOffset + accessor.byteOffset;
    size_t src_step = view.byteStride != 0 ? view.byteStride : GLwrap::getSize(gltf::toElemType(accessor.componentType));
    size_t count = accessor.count;

    extractData<In, Out>(src, src_offset, src_step,
                         dst, dst_offset, dst_step,
                         count, convert);

    // dst.resize(count);
    // loadBufferView<Out, In>(model, view, 
    //                        accessor.count, accessor.byteOffset,
    //                        dst);
};

// template<class Out, size_t S, class In>
// static void loadVecNormalizedBase(const tinygltf::Model &model,
//                                   const tinygltf::Accessor &accessor,
//                                   size_t dst_offset, std::function<float(Out)> norm,
//                                   std::vector<In> &dst){
//     using VecT = gltf::vec<Out, S>;

//     std::vector<VecT> data;                                       
//     gltf::loadAccessor<VecT, VecT>(model, accessor, data);

//     float normalized[S];
//     char* bytePtr = reinterpret_cast<char*>(dst.data()) + dst_offset;

//     // std::cout << dst.size() << std::endl;
//     for (int i = 0; i < dst.size(); ++i){
//         for (int j = 0; j < S; ++j){
//             normalized[j] = norm(data[i].data[j]);
//         }

//         memcpy(bytePtr, &normalized, sizeof(normalized));
//         bytePtr += sizeof(In);
//     }
// }

template<class T, size_t S, float (*F)(const T&)>
vec<float, S> normVec(const vec<T, S> &v){
    vec<float, S> r;
    for (int i = 0; i < S; ++i){
        r.data[i] = F(v.data[i]);
    }
    return r;
}

inline float normUByte(const unsigned char &v){
    return v / 255.0;
};

inline float normByte(const char &v){
    return std::max(v / 127.0, -1.0);
};

inline float normUShort(const unsigned short int &v){
    return v / 65535.0;
};

template<class T, size_t S>
using normFunc = std::function<vec<float,3>(const vec<T, 3>&)>;

template<size_t S>
static void loadVecNormalized(const tinygltf::Model &model,
                              const tinygltf::Accessor &accessor,
                              char *dst, size_t offset, size_t step){
    auto elem_type = gltf::toElemType(accessor.componentType);
    auto elem_struct = gltf::toElemStruct(accessor.type);

    if (GLwrap::getSize(elem_struct) != S){
        throwErr("Got invalid componentStruct.");
    }

    static normFunc<unsigned char, 3> norm = &normVec<unsigned char, S, normUByte>;
    
    static std::function<vec<float, S>(const vec<short int, S> &v)> norm_short = 
        [](const vec<short int, S> &v){
            vec<float, S> r;
            for (int i = 0; i < S; ++i){
                r.data[i] = std::max<float>(v.data[i] / 32767.0, -1.0);
            }
            return r;
        };

    // char *dst_ptr = reinterpret_cast<char *>(dst);
    
    switch (elem_type){
    case GLwrap::ElementType::UByte:
        loadAccessor<vec<unsigned char, S>, vec<float, S>>(model, accessor, dst, offset, step, &norm);
        // loadVecNormalizedBase<unsigned char, S>(model, accessor, dst_offset, norm_ubyte, dst);
        break;
        
    case GLwrap::ElementType::Byte:
        // loadVecNormalizedBase<char, S>(model, accessor, dst_offset, norm_byte, dst);
        break;

    case GLwrap::ElementType::UShort:
        // loadVecNormalizedBase<unsigned short int, S>(model, accessor, dst_offset, norm_ushort, dst);
        break;

    case GLwrap::ElementType::Short:
        loadAccessor<vec<short int, S>, vec<float, S>>(model, accessor, dst, offset, step, &norm_short);
        break;

    case GLwrap::ElementType::Float:
        loadAccessor<vec<float, S>, vec<float, S>>(model, accessor, dst, offset, step);
        break;
    
    default:
        throwErr("Got invalid indices componentType.");
    }
}

glm::mat4 loadMat4x4(const std::vector<double> &src){
    glm::mat4 mat;
    for (int i = 0; i < src.size(); ++i){
        int x = i / 4;
        int y = i % 4;
        mat[x][y] = src[i];
    }
    return mat;
}

glm::vec3 loadVec3(const std::vector<double> &src){
    glm::vec3 vec;
    for (int i = 0; i < src.size(); ++i){
        vec[i] = src[i];
    }
    return vec;
}

glm::quat loadQuat(const std::vector<double> &src){
    glm::quat quat;
    for (int i = 0; i < src.size(); ++i){
        quat[i] = src[i];
    }
    return quat;
}

}