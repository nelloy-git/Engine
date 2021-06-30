#pragma once

#include "Data/glTF.h"
#include "Data/Animation/AnimationSampler.h"

namespace Graphics {

class ModelData;
class Node;
class Animation;

class AnimationChannel {
public:
    enum class Target {
        Translation,
        Rotation,
        Scale,
        Weight
    };

    AnimationChannel(const tinygltf::AnimationChannel &channel,
                     Animation &anim, ModelData &data);
    virtual ~AnimationChannel();

    std::shared_ptr<AnimationSampler> sampler;
    std::shared_ptr<Node> node;
    Target target;
};

}