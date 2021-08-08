#pragma once

#include <vector>

#include "Draw/ModelData/IFaces/AnimCh.hpp"

namespace Graphics::Draw {

class AnimChW : public AnimCh {
public:
    AnimChW(std::shared_ptr<Node> target,
            std::shared_ptr<Buffer> time_buffer,
            std::shared_ptr<Buffer> data_buffer,
            int weights_count);
    virtual ~AnimChW();

    virtual void apply(float time, Transform &transform, std::vector<float> &morph) const override;

protected:
    void _applyLinear(float time, std::vector<float> &morph) const;

    std::vector<float> _time_list;
    std::vector<std::vector<float>> _data_list;
};

}