#pragma once

#include "glm/glm.hpp"

#include "Draw/ModelData/IFaces/AnimCh.hpp"

namespace Graphics::Draw {

class AnimChT : public AnimCh {
public:
    AnimChT(std::shared_ptr<Node> target,
            std::shared_ptr<Buffer> time_buffer,
            std::shared_ptr<Buffer> data_buffer);
    virtual ~AnimChT();

    virtual void apply(float time, Transform &transform) const override;

protected:
    void _applyLinear(float time, Transform &transform) const;

    std::vector<float> _time_list;
    std::vector<glm::vec3> _data_list;
};

}