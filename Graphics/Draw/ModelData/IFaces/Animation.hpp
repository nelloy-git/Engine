#pragma once

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Draw/ModelData/IFaces/AnimationChannel.hpp"

namespace Graphics::Draw {

class Model;

class Animation {
public:
    Animation(const Model &mode, int index) :
        model(model),
        index(index){}

    virtual ~Animation(){}

    const Model &model;
    const int index;

    std::vector<std::shared_ptr<AnimationChannelTranslate>> translations;
    std::vector<std::shared_ptr<AnimationChannelRotate>> rotations;
    std::vector<std::shared_ptr<AnimationChannelScale>> scales;
    std::vector<std::shared_ptr<AnimationChannelWeight>> weights;
};

}