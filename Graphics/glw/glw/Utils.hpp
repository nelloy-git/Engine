#pragma once

#include "glad/gl.h"
// #include "magic_enum.hpp"

#include "glw/Types.hpp"

namespace glw {

// static_assert(magic_enum::is_magic_enum_supported, "Magic enum is not supported");

namespace detailed {
    template<gpu_data_type DT> struct cpu_data_type;
    template<> struct cpu_data_type<gpu_data_type::GLbyte>{using type = GLbyte;};
    template<> struct cpu_data_type<gpu_data_type::GLubyte>{using type = GLubyte;};
    template<> struct cpu_data_type<gpu_data_type::GLshort>{using type = GLshort;};
    template<> struct cpu_data_type<gpu_data_type::GLushort>{using type = GLushort;};
    template<> struct cpu_data_type<gpu_data_type::GLint>{using type = GLint;};
    template<> struct cpu_data_type<gpu_data_type::GLuint>{using type = GLuint;};
    template<> struct cpu_data_type<gpu_data_type::GLfloat>{using type = GLfloat;};
    template<> struct cpu_data_type<gpu_data_type::GLuint_2_10_10_10>{using type = uint32_t;};
    template<> struct cpu_data_type<gpu_data_type::GLuint_10_11_11>{using type = uint32_t;};
    template<> struct cpu_data_type<gpu_data_type::GLint_2_10_10_10>{using type = uint32_t;};

    template < template <typename...> class base,typename derived>
    struct is_base_of_template_impl
    {
        template<typename... Ts>
        static constexpr std::true_type  test(const base<Ts...> *);
        static constexpr std::false_type test(...);
        using type = decltype(test(std::declval<derived*>()));
    };

    template < template <typename...> class base, typename derived>
    using is_base_of_template = typename is_base_of_template_impl<base,derived>::type;

    template<bool... b> constexpr bool var_and = (b && ...);
    template<bool... b> constexpr bool var_or = (b || ...);
    template<class T, class... Any> constexpr bool is_same_any = (std::is_same_v<T, Any> || ...);
};

template<gpu_data_type DT>
using cpu_data_type_t = typename detailed::cpu_data_type<DT>::type;

inline constexpr size_t size(gpu_data_type data_type){
    switch (data_type){
        case gpu_data_type::GLbyte:
            return sizeof(cpu_data_type_t<gpu_data_type::GLbyte>);
        case gpu_data_type::GLubyte:
            return sizeof(gpu_data_type::GLubyte);
        case gpu_data_type::GLshort:
            return sizeof(gpu_data_type::GLshort);
        case gpu_data_type::GLushort:
            return sizeof(gpu_data_type::GLushort);
        case gpu_data_type::GLint:
            return sizeof(gpu_data_type::GLint);
        case gpu_data_type::GLuint:
            return sizeof(gpu_data_type::GLuint);
        case gpu_data_type::GLfloat:
            return sizeof(gpu_data_type::GLfloat);
        case gpu_data_type::GLdouble:
            return sizeof(gpu_data_type::GLdouble);
        case gpu_data_type::GLint_2_10_10_10:
            return sizeof(gpu_data_type::GLint_2_10_10_10);
        case gpu_data_type::GLuint_2_10_10_10:
            return sizeof(gpu_data_type::GLuint_2_10_10_10);
        case gpu_data_type::GLuint_10_11_11:
            return sizeof(gpu_data_type::GLuint_10_11_11);
        default:
            // Unknown ElementType
            assert(false);
    }
};

inline constexpr size_t count(DataSize data_size){
    switch (data_size){
        case DataSize::Scalar:
            return 1;
        case DataSize::Vec2:
            return 2;
        case DataSize::Vec3:
            return 3;
        case DataSize::Vec4:
            return 4;
        case DataSize::Mat3:
            return 9;
        case DataSize::Mat4:
            return 16;
        default:
            assert(false);
    }
};

inline constexpr GLenum gl(gpu_data_type type){
    return static_cast<GLenum>(type);
}

inline constexpr GLenum gl(BufferType type){
    return static_cast<GLenum>(type);
}

inline constexpr GLenum gl(BufferUsage usage){
    return static_cast<GLenum>(usage);
}

inline constexpr GLenum gl(DrawMode mode){
    return static_cast<GLenum>(mode);
}

inline constexpr GLenum gl(ShaderType type){
    return static_cast<GLenum>(type);
}

inline constexpr GLenum gl(Tex2DInternalFormat fmt){
    return static_cast<GLenum>(fmt);
}

inline constexpr GLenum gl(Tex2DPixelDataFormat fmt){
    return static_cast<GLenum>(fmt);
}

inline constexpr GLenum gl(Tex2DPixelDataType type){
    return static_cast<GLenum>(type);
}

inline constexpr GLenum gl(Tex2DWrap wrap){
    return static_cast<GLenum>(wrap);
}

inline constexpr GLenum gl(Tex2DFilter filter){
    return static_cast<GLenum>(filter);
}


// template<typename T>
// inline constexpr std::string str(T enum_v){
//     constexpr auto type_name = magic_enum::enum_type_name<T>();
//     auto enum_name = magic_enum::enum_name(enum_v);
//     return std::string(type_name) + std::string("::") + std::string(enum_name);
// }

} // namespace GLwrap