#pragma once

#include <vector>

#include "Draw/ModelData/IFaces/AnimCh.hpp"
#include "Draw/ModelData/IFaces/AnimCh/AnimChR.hpp"

namespace Graphics::Draw {

class Object;

class Animation {
public:
    Animation(const Model &mode, int index);
    virtual ~Animation();

    const Model &model;
    const int index;

    void apply(float time, Object &obj);

    std::vector<std::shared_ptr<AnimCh>> channels;

    // std::vector<std::shared_ptr<AnimChT>> translations;
    // std::vector<std::shared_ptr<AnimChR>> rotations;
    // std::vector<std::shared_ptr<AnimationChannelScale>> scales;
    // std::vector<std::shared_ptr<AnimationChannelWeight>> weights;
};

}