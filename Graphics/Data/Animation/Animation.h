#pragma once

#include "Data/glTF.h"
#include "Data/Animation/AnimationChannel.h"
#include "Data/Animation/AnimationSampler.h"

namespace Graphics {

class ModelData;

class Animation {
public:
    Animation(const tinygltf::Animation &anim,
              const tinygltf::Model &model,
              ModelData &data);
    virtual ~Animation();

    std::vector<std::shared_ptr<AnimationChannel>> channels;
    std::vector<std::shared_ptr<AnimationSampler>> samplers;

};

}