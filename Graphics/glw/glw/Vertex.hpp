#pragma once

#include <iostream>

#include "glad/gl.h"

#include "glw/Attribute.hpp"
#include "glw/Utils.hpp"

namespace glw {


template<class ... A>
class Vertex {
    static_assert(detailed::var_and<detailed::is_base_of_template<Attribute, A>::value...>);
    static_assert(sizeof...(A) <= 16);
    static_assert((sizeof(A) + ...) <= 16 * 4 * sizeof(float));

public:
    using Tuple = std::tuple<A...>; 
    template<size_t N>
    using Attribute = typename std::tuple_element_t<N, Tuple>;

    static void bindAttributes(){
        GLuint loc = 0;
        size_t offset = 0;
        ([&](){
            A::Meta::enable(loc, sizeof(Vertex), offset);
            loc++;
            offset += sizeof(A);
        }(), ...);
    }

    Tuple attributes;

    template<size_t N>
    inline decltype(auto) getAttr(){
        return std::get<N>(attributes);
    }

    template<size_t N, class ... T>
    inline decltype(auto) set(T ... v){
        return std::get<N>(attributes).set(v...);
    }

};

}