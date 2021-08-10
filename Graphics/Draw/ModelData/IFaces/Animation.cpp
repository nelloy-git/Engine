#include "Draw/ModelData/IFaces/Animation.hpp"

#include "Draw/Object.hpp"
#include "Log.h"

using namespace Graphics::Draw;

template<typename T>
using Uptr = Animation::Uptr<T>;

Animation::Animation(const Model *model, int index) :
    ModelData(model, index){
    channels.resize(model->getNodesCount());
}


Animation::~Animation(){
}


bool Animation::apply(const Node &node,
                      float time,
                      Transform &trans,
                      std::vector<float> &morph) const {
    auto list = _getAnimChList(node);
    if (!list){
        return false;
    }

    trans = node.transform;
    morph = node.mesh ? node.mesh->morph : std::vector<float>();

    for (int i = 0; i < list->size(); ++i){
        list->at(i)->apply(time, trans, morph);
    }
    trans.applyTRS();

    return true;
}

const std::vector<Uptr<AnimCh>> *Animation::_getAnimChList(const Node &node) const {
    int node_i = node.index;
    if (node_i < 0 || node_i >= _channels.size()){
        return nullptr;
    }
    return &_channels[node_i];
}

AnimCh *Animation::_getAnimCh(const Node &node, int i) const {
    auto list = _getAnimChList(node);
    if (!list){
        return nullptr;
    }

    if (i < 0 || i >= list->size()){
        return nullptr;
    }

    return list->at(i).get();
}