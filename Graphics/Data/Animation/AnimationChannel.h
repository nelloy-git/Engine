#pragma once

#include "Data/glTF.h"
#include "Data/Animation/AnimationSampler.h"

namespace Graphics {

class Node;

enum class AnimationTarget {
    Translation,
    Rotation,
    Scale,
    Weight
};

template<AnimationTarget T>
class AnimationChannel {
public:

    AnimationChannel(std::shared_ptr<Node> node,
                     std::shared_ptr<AnimationSampler<T>> sampler);
    virtual ~AnimationChannel();

    const AnimationTarget target = T;
    std::shared_ptr<Node> node;
    std::shared_ptr<AnimationSampler<T>> sampler;
};

}