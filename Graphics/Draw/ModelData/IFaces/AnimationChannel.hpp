#pragma once

#include <variant>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Draw/ModelData/IFaces/Node.hpp"

namespace Graphics::Draw {

class AnimationChannel {
public:
    AnimationChannel() = default;
    virtual ~AnimationChannel() = 0;

    std::shared_ptr<Node> node;
    std::vector<float> time;
};

AnimationChannel::~AnimationChannel(){
}

class AnimationChannelTranslate : public AnimationChannel {
public:
    AnimationChannelTranslate() = default;
    virtual ~AnimationChannelTranslate() = default;

    glm::vec3 get(float time, Interpolation method);
    std::vector<glm::vec3> data;
};

class AnimationChannelRotate : public AnimationChannel {
public:
    AnimationChannelRotate() = default;
    virtual ~AnimationChannelRotate() = default;

    glm::quat get(float time, Interpolation method);
    std::vector<glm::quat> data;
};

class AnimationChannelScale : public AnimationChannel {
public:
    AnimationChannelScale() = default;
    virtual ~AnimationChannelScale() = default;

    glm::vec3 get(float time, Interpolation method);
    std::vector<glm::vec3> data;
};

class AnimationChannelWeight : public AnimationChannel {
public:
    AnimationChannelWeight() = default;
    virtual ~AnimationChannelWeight() = default;

    std::vector<float> get(float time, Interpolation method);
    std::vector<std::vector> data;
};

}