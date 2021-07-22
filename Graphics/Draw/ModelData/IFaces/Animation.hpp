#pragma once

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Draw/ModelData/IFaces/AnimationChannel.hpp"

namespace Graphics::Draw {

class Model;

class Animation {
public:
    const Model &model;
    const int index;

    std::vector<std::shared_ptr<AnimationChannelTranslate>> translations;
    std::vector<std::shared_ptr<AnimationChannelRotate>> rotations;
    std::vector<std::shared_ptr<AnimationChannelScale>> scales;
    std::vector<std::shared_ptr<AnimationChannelWeight>> weights;
};

}