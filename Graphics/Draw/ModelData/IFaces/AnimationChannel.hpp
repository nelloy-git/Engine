#pragma once

#include <variant>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Draw/ModelData/IFaces/Buffer.hpp"
#include "Draw/ModelData/IFaces/Node.hpp"

namespace Graphics::Draw {

class AnimationChannel {
public:
    AnimationChannel(std::shared_ptr<Node> target,
                     const Buffer &time_buffer);
    virtual ~AnimationChannel() = 0;

    std::shared_ptr<Node> node;
    std::vector<float> time;

protected:
    static float _getNormalized(const Buffer &buffer, size_t pos);
};

class AnimationChannelTranslate : public AnimationChannel {
public:
    AnimationChannelTranslate(std::shared_ptr<Node> target,
                              const Buffer &time_buffer,
                              const Buffer &data_buffer);
    virtual ~AnimationChannelTranslate();

    glm::vec3 get(float time, Interpolation method);
    std::vector<glm::vec3> data;
};

class AnimationChannelRotate : public AnimationChannel {
public:
    AnimationChannelRotate(std::shared_ptr<Node> target,
                           const Buffer &time_buffer,
                           const Buffer &data_buffer);
    virtual ~AnimationChannelRotate();

    glm::quat get(float time, Interpolation method);
    std::vector<glm::quat> data;
};

class AnimationChannelScale : public AnimationChannel {
public:
    AnimationChannelScale(std::shared_ptr<Node> target,
                          const Buffer &time_buffer,
                          const Buffer &data_buffer);
    virtual ~AnimationChannelScale();

    glm::vec3 get(float time, Interpolation method);
    std::vector<glm::vec3> data;
};

class AnimationChannelWeight : public AnimationChannel {
public:
    AnimationChannelWeight(std::shared_ptr<Node> target,
                           const Buffer &time_buffer,
                           const Buffer &data_buffer);
    virtual ~AnimationChannelWeight();

    std::vector<float> get(float time, Interpolation method);
    std::vector<std::vector<float>> data;
};

}