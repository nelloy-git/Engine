#pragma once

#include "glm/glm.hpp"

#include "Graphics/ModelData/IFaces/AnimCh.hpp"

namespace Graphics::Draw {

class AnimChT : public AnimCh {
public:
    AnimChT(const Node &target,
            const Buffer &time_buffer,
            const Buffer &data_buffer);
    virtual ~AnimChT();

    virtual void apply(float time, Transform &transform, std::vector<float> &morph) const override;

protected:
    void _applyLinear(float time, Transform &transform) const;

    std::vector<float> _time_list;
    std::vector<glm::vec3> _data_list;
};

}