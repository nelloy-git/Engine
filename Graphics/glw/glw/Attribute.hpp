#pragma once

#include <array>
#include <tuple>

#include "glw/Utils.hpp"

namespace glw {

template<gpu_data_type _DT, size_t _S, bool _N>
struct AttributeMeta {
private:
    static constexpr bool _is_3_components_only = _DT == gpu_data_type::GLuint_10_11_11;
    static constexpr bool _is_4_components_only = _DT == gpu_data_type::GLint_2_10_10_10
                                               || _DT == gpu_data_type::GLuint_2_10_10_10;

    static_assert(_S >= 1 && _S <=4);
    static_assert(!(_is_3_components_only && _S != 3));
    static_assert(!(_is_4_components_only && _S != 4));
    
public:
    static constexpr bool Packed = _DT == gpu_data_type::GLuint_10_11_11
                                || _DT == gpu_data_type::GLint_2_10_10_10
                                || _DT == gpu_data_type::GLuint_2_10_10_10;
                    
    static constexpr bool Signed = !(_DT == gpu_data_type::GLubyte
                                   || _DT == gpu_data_type::GLushort
                                   || _DT == gpu_data_type::GLuint
                                   || _DT == gpu_data_type::GLuint_10_11_11
                                   || _DT == gpu_data_type::GLuint_2_10_10_10);
                                   
    static constexpr bool Norm = _N;        // Should data be normalized in GPU
    static constexpr gpu_data_type Type = _DT;   // OpenGL data type
    static constexpr size_t Size = _S;      // OpenGL data size 
    
    static void enable(GLuint loc, GLsizei step, size_t offset){
        glEnableVertexAttribArray(loc);
        glVertexAttribPointer(loc, Size, glw::gl(Type),
                              Norm ? GL_TRUE : GL_FALSE,
                              step, (void*)offset);
    }
};

template<class AM>
struct Attribute {
    using Meta = AM; 
    using ComponentType = cpu_data_type_t<Meta::Type>;
    using RawType = std::array<ComponentType, Meta::Packed ? 1 : Meta::Size>;

    RawType raw;

    // Direct

    template<size_t S = Meta::Size, bool P = Meta::Packed, bool N = Meta::Norm, 
             std::enable_if_t<(S == 1 && !P && !N)>* = nullptr> 
    inline void set(const ComponentType &x){
        raw = {x};
    }

    template<size_t S = Meta::Size, bool P = Meta::Packed, bool N = Meta::Norm, 
             std::enable_if_t<(S == 2 && !P && !N)>* = nullptr>
    inline void set(const ComponentType &x, const ComponentType &y){
        raw = {x, y};
    }

    template<size_t S = Meta::Size, bool P = Meta::Packed, bool N = Meta::Norm, 
             std::enable_if_t<(S == 3 && !P && !N)>* = nullptr>
    inline void set(const ComponentType &x, const ComponentType &y, const ComponentType &z){
        raw = {x, y, z};
    }

    template<size_t S = Meta::Size, bool P = Meta::Packed, bool N = Meta::Norm, 
             std::enable_if_t<(S == 4 && !P && !N)>* = nullptr>
    inline void set(const ComponentType &x, const ComponentType &y,
                    const ComponentType &z, const ComponentType &w){
        raw = {x, y, z, w};
    }

    // Normalized

    template<size_t S = Meta::Size, bool P = Meta::Packed, bool N = Meta::Norm, 
             std::enable_if_t<(S == 1 && !P && N)>* = nullptr>
    inline void set(float x){
        raw = {_norm(x)};
    }

    template<size_t S = Meta::Size, bool P = Meta::Packed, bool N = Meta::Norm, 
             std::enable_if_t<(S == 2 && !P && N)>* = nullptr>
    inline void set(float x, float y){
        raw = {_norm(x), _norm(y)};
    }

    template<size_t S = Meta::Size, bool P = Meta::Packed, bool N = Meta::Norm, 
             std::enable_if_t<(S == 3 && !P && N)>* = nullptr>
    inline void set(float x, float y, float z){
        raw = {_norm(x), _norm(y), _norm(z)};
    }

    template<size_t S = Meta::Size, bool P = Meta::Packed, bool N = Meta::Norm, 
             std::enable_if_t<(S == 4 && !P && N)>* = nullptr>
    inline void set(float x, float y, float z, float w){
        raw = {_norm(x), _norm(y), _norm(z), _norm(w)};
    }

    // Packed

    template<gpu_data_type T = Meta::Type, bool N = Meta::Norm,
             std::enable_if_t<(T == gpu_data_type::GLint_2_10_10_10 && N)>* = nullptr>
    inline void set(float x, float y, float z, float w){
        x = _normBorder(x);
        y = _normBorder(y);
        z = _normBorder(z);
        w = _normBorder(w);

        const uint32_t xs = x < 0 ? 1 : 0;
        const uint32_t ys = y < 0 ? 1 : 0;
        const uint32_t zs = z < 0 ? 1 : 0;
        const uint32_t ws = w < 0 ? 1 : 0; 
        raw[0] = xs << 9 | ((uint32_t)(x * 511 + (xs << 9)) & 511)
                 | ys << 19 | (((uint32_t)(y * 511 + (ys << 9)) & 511) << 10)
                 | zs << 29 | (((uint32_t)(z * 511 + (zs << 9)) & 511) << 20)
                 | ws << 31 | (((uint32_t)(w + (ws << 1)) & 1) << 30);
    }


    // template<gpu_data_type T = Meta::Type, bool N = Meta::Norm,
    //          std::enable_if_t<(T == gpu_data_type::UInt_2_10_10_10 && N)>* = nullptr>
    // inline void set(float x, float y, float z, float w){
    //     static_assert(false, "TODO");
    // }

    // template<gpu_data_type T = Meta::Type, bool N = Meta::Norm,
    //          std::enable_if_t<(T == gpu_data_type::UInt_10_11_11 && N)>* = nullptr>
    // inline void set(float x, float y, float z){
    //     static_assert(false, "TODO");
    // }

private:

    template<bool N = Meta::Norm, std::enable_if_t<(N)>* = nullptr>
    inline float _normBorder(float v){
        if constexpr (Meta::Signed){
            return (v > 1) ? 1 : (v < -1) ? -1 : v;
        } else {
            return (v > 1) ? 1 : (v < 0) ? 0 : v;
        }
    }

    template<bool N = Meta::Norm, std::enable_if_t<(N)>* = nullptr>
    inline ComponentType _norm(float v){
        v = _normBorder(v);

        if constexpr (Meta::Type == gpu_data_type::GLubyte){
            return v * 255.0;
        } else if constexpr (Meta::Type == gpu_data_type::GLbyte){
            return v * 127.0;
        } else if constexpr (Meta::Type == gpu_data_type::GLushort){
            return v * 65535.0;
        } else if constexpr (Meta::Type == gpu_data_type::GLshort){
            return v * 32767.0;
        } else if constexpr (Meta::Type == gpu_data_type::GLfloat){
            return v;
        } else {
            []<bool F = false>(){static_assert(F, "type can not be normalized.");}();
        }
    }
};

}