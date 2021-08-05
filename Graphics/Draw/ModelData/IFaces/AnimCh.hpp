#pragma once

#include <vector>

#include "Draw/ModelData/IFaces/Buffer.hpp"
#include "Draw/ModelData/IFaces/Node.hpp"

namespace Graphics::Draw {

class AnimCh {
public:
    AnimCh(std::shared_ptr<Node> target,
           std::shared_ptr<Buffer> time_buffer,
           std::shared_ptr<Buffer> data_buffer,
           Interpolation method = Interpolation::Linear);
    virtual ~AnimCh();

    virtual void apply(float time, Transform &transform, std::vector<float> &morph) const = 0;

    const std::shared_ptr<Node> getTarget() const;
    const std::shared_ptr<Buffer> getTime() const;
    const std::shared_ptr<Buffer> getData() const;
    Interpolation getMethod() const;
    
protected:
    static float _getNormFloat(const Buffer &buffer, size_t pos);
    
    std::shared_ptr<Node> _target;
    std::shared_ptr<Buffer> _time;
    std::shared_ptr<Buffer> _data;
    Interpolation _method;
};

}