#pragma once

#include "glm/glm.hpp"

#include "Draw/ModelData/IFaces/AnimCh.hpp"

namespace Graphics::Draw {

class AnimChS : public AnimCh {
public:
    AnimChS(const Node &target,
            const Buffer &time_buffer,
            const Buffer &data_buffer);
    virtual ~AnimChS();

    virtual void apply(float time, Transform &transform, std::vector<float> &morph) const override;

protected:
    void _applyLinear(float time, Transform &transform) const;

    std::vector<float> _time_list;
    std::vector<glm::vec3> _data_list;
};

}