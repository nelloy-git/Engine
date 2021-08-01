#include "Draw/ModelData/IFaces/Animation.hpp"

#include "Draw/Object.hpp"

using namespace Graphics::Draw;

Animation::Animation(const Model &mode, int index) :
    model(model),
    index(index){
}


Animation::~Animation(){
}


void Animation::apply(float time, Object &obj){
    for (auto chan : channels){
        auto &targ = obj._node_transforms[chan->getTarget()->index];
        chan->apply(time, targ);
    }
};