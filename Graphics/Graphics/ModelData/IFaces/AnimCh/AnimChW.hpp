#pragma once

#include <vector>

#include "Graphics/ModelData/IFaces/AnimCh.hpp"

namespace Graphics::Draw {

class AnimChW : public AnimCh {
public:
    AnimChW(const Node &target,
            const Buffer &time_buffer,
            const Buffer &data_buffer,
            int weights_count);
    virtual ~AnimChW();

    virtual void apply(float time, Transform &transform, std::vector<float> &morph) const override;

protected:
    void _applyLinear(float time, std::vector<float> &morph) const;

    std::vector<float> _time_list;
    std::vector<std::vector<float>> _data_list;
};

}