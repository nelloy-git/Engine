#pragma once

#include <vector>

#include "Draw/ModelData/IFaces/Buffer.hpp"
#include "Draw/ModelData/IFaces/Node.hpp"

namespace Graphics::Draw {

class AnimCh {
public:
    AnimCh(Node *target,
           Buffer *time_buffer,
           Buffer *data_buffer,
           Interpolation method = Interpolation::Linear);
    virtual ~AnimCh();

    virtual void apply(float time, Transform &transform, std::vector<float> &morph) const = 0;

    const Node *getTarget() const;
    const Buffer *getTime() const;
    const Buffer *getData() const;
    Interpolation getMethod() const;
    
protected:
    static float _getNormFloat(const Buffer &buffer, size_t pos);
    
    Node *_target;
    Buffer *_time;
    Buffer *_data;
    Interpolation _method;
};

}