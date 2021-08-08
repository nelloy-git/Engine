#pragma once

#include <vector>

#include "Draw/ModelData/IFaces/AnimCh.hpp"
#include "Draw/ModelData/IFaces/AnimCh/AnimChR.hpp"

namespace Graphics::Draw {

class Object;

class Animation {
public:
    Animation(const Model &model, int index);
    virtual ~Animation();

    const Model &model;
    const int index;

    void getMat(const Node &node, float time, glm::mat4 *mat, std::vector<float> *morph);

    // node.index -> list of channels for node -> channel
    std::vector<std::vector<std::shared_ptr<AnimCh>>> channels;

private:
    float min_time = -1;
    float max_time = -1;
};

}