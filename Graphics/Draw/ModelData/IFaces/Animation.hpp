#pragma once

#include <vector>

#include "Draw/ModelData/IFaces/ModelData.h"
#include "Draw/ModelData/IFaces/AnimCh.hpp"
#include "Draw/ModelData/IFaces/AnimCh/AnimChR.hpp"
#include "Draw/ModelData/IFaces/AnimCh/AnimChS.hpp"
#include "Draw/ModelData/IFaces/AnimCh/AnimChT.hpp"
#include "Draw/ModelData/IFaces/AnimCh/AnimChW.hpp"

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

protected:
    template<typename T>
    using Uptr = std::unique_ptr<T>;

    const std::vector<Uptr<AnimCh>> *_getAnimChList(const Node &node) const;
    AnimCh *_getAnimCh(const Node &node, int i) const;

    AnimChT *_addChT(const Node &target, const Buffer &time_buffer, const Buffer &data_buffer);
    AnimChR *_addChR(const Node &target, const Buffer &time_buffer, const Buffer &data_buffer);
    AnimChS *_addChS(const Node &target, const Buffer &time_buffer, const Buffer &data_buffer);
    AnimChW *_addChW(const Node &target, const Buffer &time_buffer, const Buffer &data_buffer, int morph_size);

    std::vector<std::vector<Uptr<AnimCh>>> _channels;
};

}