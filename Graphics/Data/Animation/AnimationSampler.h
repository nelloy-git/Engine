#pragma once

#include <variant>

#include <glm/glm.hpp>

#include "Data/glTF.h"

namespace Graphics {

class ModelData;

template<typename T>
class AnimationSampler {
public:
    AnimationSampler(float min_time, float max_time) :
        min_time(min_time),
        max_time(max_time){
    };
    virtual ~AnimationSampler(){};

    float min_time;
    float max_time;
    std::unordered_map<float, T> frames;
};

}