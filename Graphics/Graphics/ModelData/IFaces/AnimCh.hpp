#pragma once

#include <vector>

#include "Graphics/ModelData/IFaces/Buffer.hpp"
#include "Graphics/ModelData/IFaces/Node.hpp"

namespace Graphics::Draw {

class AnimCh {
public:
    AnimCh(const Node &target,
           const Buffer &time_buffer,
           const Buffer &data_buffer,
           Interpolation method = Interpolation::Linear);
    virtual ~AnimCh();

    virtual void apply(float time, Transform &transform, std::vector<float> &morph) const = 0;

    const Node &getTarget() const;
    const Buffer &getTime() const;
    const Buffer &getData() const;
    Interpolation getMethod() const;
    
protected:
    static float _getNormFloat(const Buffer &buffer, size_t pos);
    
    const Node &_target;
    const Buffer &_time;
    const Buffer &_data;
    Interpolation _method;
};

}