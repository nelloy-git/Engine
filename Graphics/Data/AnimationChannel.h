#pragma once

#include "Data/glTF.h"

namespace Graphics {

class ModelData;

class AnimationChannel {

public:
    enum class Interpolation {
        LINEAR,
    };

public:
    AnimationChannel(const tinygltf::Model &model,
                     const ModelData &data);
    virtual ~AnimationChannel();

    Interpolation inter;
    
    
};

}