#pragma once

#include <vector>

#include "Draw/ModelData/IFaces/ModelData.h"
#include "Draw/ModelData/IFaces/AnimCh.hpp"

namespace Graphics::Draw {

class Animation : public ModelData {
friend class ModelLoader;

public:
    Animation(const Model *model, int index);
    virtual ~Animation() override;

    bool apply(const Node &node,
               float time,
               Transform &trans,
               std::vector<float> &morph) const;

private:
    template<typename T>
    using Uptr = std::unique_ptr<T>;

    const std::vector<Uptr<AnimCh>> *_getAnimChList(const Node &node) const;
    AnimCh *_getAnimCh(const Node &node, int i) const;

    AnimChT *addChT(const Node *target, const Buffer *time_buffer, const Buffer *data_buffer);
    AnimChR *addChR(const Node *target, const Buffer *time_buffer, const Buffer *data_buffer);
    AnimChS *addChS(const Node *target, const Buffer *time_buffer, const Buffer *data_buffer);
    AnimChS *addChW(const Node *target, const Buffer *time_buffer, const Buffer *data_buffer, int morph_size);

    std::vector<std::vector<Uptr<AnimCh>>> _channels;
};

}