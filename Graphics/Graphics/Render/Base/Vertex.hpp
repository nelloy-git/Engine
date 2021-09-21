#pragma once

#include <cmath>
#include <functional>

#include "GLwrap/Array.h"

namespace Graphics::Render::Base {

struct VertexStruct {
    const GLwrap::ElementStruct POS;
    const GLwrap::ElementStruct NORM;
    const GLwrap::ElementStruct TANG;

    const size_t COLOR_COUNT;
    const GLwrap::ElementStruct COLOR;

    const size_t TEX_COORD_COUNT;
    const GLwrap::ElementStruct TEX_COORD;

    const size_t JOINTS_COUNT;
    const GLwrap::ElementStruct JOINTS;
    const GLwrap::ElementStruct WEIGHTS;

    const size_t MORPH_COUNT;
    const GLwrap::ElementStruct MORPH;

    const size_t CUSTOM_COUNT;
    const GLwrap::ElementStruct CUSTOM;
};

template<VertexStruct S>
class Vertex final {
public:
    ~Vertex() noexcept {
        // Max size of OpenGL vertex attributes is 16xVec4f
        static_assert(sizeof(Vertex<S>) <= 16 * 4 * sizeof(float));
    }

    float pos[GLwrap::getSize(S.POS)];
    float norm[GLwrap::getSize(S.NORM)];
    float tang[GLwrap::getSize(S.TANG)];

    float color[S.COLOR_COUNT][GLwrap::getSize(S.COLOR)];
    float tex_coord[S.TEX_COORD_COUNT][GLwrap::getSize(S.TEX_COORD)];
    float joints[S.JOINTS_COUNT][GLwrap::getSize(S.JOINTS)];
    float weights[S.JOINTS_COUNT][GLwrap::getSize(S.WEIGHTS)];
    float morph[S.MORPH_COUNT][GLwrap::getSize(S.MORPH)];
    float custom[S.CUSTOM_COUNT][GLwrap::getSize(S.CUSTOM)];
};

}