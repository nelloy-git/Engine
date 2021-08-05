#pragma once

#include "glm/gtc/quaternion.hpp"

#include "Draw/ModelData/IFaces/AnimCh.hpp"

namespace Graphics::Draw {

class AnimChR : public AnimCh {
public:
    AnimChR(std::shared_ptr<Node> target,
            std::shared_ptr<Buffer> time_buffer,
            std::shared_ptr<Buffer> data_buffer);
    virtual ~AnimChR();

    virtual void apply(float time, Transform &transform, std::vector<float> &morph) const override;

protected:
    void _applyLinear(float time, Transform &transform) const;

    std::vector<float> _time_list;
    std::vector<glm::quat> _data_list;
};

}