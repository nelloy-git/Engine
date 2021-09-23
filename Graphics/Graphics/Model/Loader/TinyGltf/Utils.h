#pragma once

#include <functional>
#include <variant>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Graphics/Model/Loader/TinyGltf/Types.h"

namespace Graphics::Model::gltf::detailed {
    
template<class T, size_t S>
struct vec {
    T data[S];
};

template<class InT, size_t InS, class OutT, size_t OutS>
using ConvF = std::function<vec<OutT, OutS>(const vec<InT, InS>&)>;

template<class R, class Out, class In>
constexpr R min(const Out &v1, const In &v2){
    return v1 > v2 ? v2 : v1;
}

template<class InT, size_t InS, class OutT, size_t OutS>
void extractData(const char *src, size_t src_offset, size_t src_step,
                 char *dst, size_t dst_offset, size_t dst_step,
                 size_t count){
    char *src_addr = const_cast<char *>(src) + src_offset;
    char *dst_addr = dst + dst_offset;
    size_t block_size = std::min(sizeof(vec<InT, InS>), sizeof(vec<OutT, OutS>));
    
    for (int i = 0; i < count; ++i){
        memcpy(dst_addr, src_addr, block_size);
        src_addr += src_step;
        dst_addr += dst_step;
    }
};

template<class InT, size_t InS, class OutT, size_t OutS>
void extractData(const char *src, size_t src_offset, size_t src_step,
                 char *dst, size_t dst_offset, size_t dst_step,
                 size_t count, ConvF<InT, InS, OutT, OutS> convert){
    char *src_addr = const_cast<char *>(src) + src_offset;
    char *dst_addr = dst + dst_offset;
    
    for (int i = 0; i < count; ++i){
        vec<InT, InS> *in = reinterpret_cast<vec<InT, InS> *>(src_addr);
        vec<OutT, OutS> *out = reinterpret_cast<vec<OutT, OutS> *>(dst_addr);
        *out = convert(*in);

        src_addr += src_step;
        dst_addr += dst_step;
    }
};

// convert == nullptr should bug with big-endian data.
template<class InT, size_t InS, class OutT, size_t OutS>
void loadAccessor(const tinygltf::Model &model,
                  const tinygltf::Accessor &accessor,
                  char *dst, size_t dst_offset, size_t dst_step,
                  ConvF<InT, InS, OutT, OutS> *convert = nullptr){
    auto &view = model.bufferViews[accessor.bufferView];
    auto src_type = gltf::getElemType(accessor);
    auto src_struct = gltf::getElemStruct(accessor);
    auto src_size = GLwrap::getSize(src_type) * GLwrap::getSize(src_struct);

    const char *src = reinterpret_cast<const char *>(model.buffers[view.buffer].data.data());
    size_t src_offset = view.byteOffset + accessor.byteOffset;
    size_t src_step = view.byteStride != 0 ? view.byteStride : src_size;
    size_t count = accessor.count;

    if (convert){
        extractData<InT, InS, OutT, OutS>(src, src_offset, src_step,
                                          dst, dst_offset, dst_step,
                                          count, *convert);
    } else {
        extractData<InT, InS, OutT, OutS>(src, src_offset, src_step,
                                          dst, dst_offset, dst_step,
                                          count);
    }    
};

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

inline float normShort(const short int &v){
    return std::max<float>(v / 32767.0, -1.0);
};

inline float normDouble(const double &v){
    return v;
};

template<class T, size_t S>
using normFunc = std::function<vec<float,S>(const vec<T, S>&)>;

template<size_t S>
static void loadVecNormalized(const tinygltf::Model &model,
                              const tinygltf::Accessor &accessor,
                              char *dst, size_t offset, size_t step){
    auto elem_type = gltf::getElemType(accessor);
    auto elem_struct = gltf::getElemStruct(accessor);

    if (GLwrap::getSize(elem_struct) != S){
        throwErr("Got invalid componentStruct.");
    }

    static normFunc<unsigned char, S> norm_ubyte = &normVec<unsigned char, S, normUByte>;
    static normFunc<char, S> norm_byte = &normVec<char, S, normByte>;
    static normFunc<unsigned short int, S> norm_ushort = &normVec<unsigned short int, S, normUShort>;
    static normFunc<short int, S> norm_short = &normVec<short int, S, normShort>;
    static normFunc<double, S> norm_double = &normVec<double, S, normDouble>;
    
    switch (elem_type){
    case GLwrap::ElementType::UByte:
        loadAccessor<unsigned char, S, float, S>(model, accessor, dst, offset, step, &norm_ubyte);
        break;
        
    case GLwrap::ElementType::Byte:
        loadAccessor<char, S, float, S>(model, accessor, dst, offset, step, &norm_byte);
        break;

    case GLwrap::ElementType::UShort:
        loadAccessor<unsigned short int, S, float, S>(model, accessor, dst, offset, step, &norm_ushort);
        break;

    case GLwrap::ElementType::Short:
        loadAccessor<short int, S, float, S>(model, accessor, dst, offset, step, &norm_short);
        break;

    case GLwrap::ElementType::Float:
        loadAccessor<float, S, float, S>(model, accessor, dst, offset, step);
        break;

    case GLwrap::ElementType::Double:
        loadAccessor<double, S, float, S>(model, accessor, dst, offset, step, &norm_double);
        break;
    
    default:
        throwErr("Got invalid indices componentType.");
    }
}

}