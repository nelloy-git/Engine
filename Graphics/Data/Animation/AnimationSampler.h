#pragma once

#include <variant>

#include <glm/glm.hpp>

#include "Data/glTF.h"

namespace Graphics {

class ModelData;

class AnimationSampler {
public:
    typedef std::variant<float, glm::vec3, glm::vec4> Data;

    AnimationSampler(const tinygltf::AnimationSampler &sampler,
                     ModelData &data);
    virtual ~AnimationSampler();

    std::vector<std::pair<float, Data>> times;
};

}