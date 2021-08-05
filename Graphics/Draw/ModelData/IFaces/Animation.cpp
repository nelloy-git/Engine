#include "Draw/ModelData/IFaces/Animation.hpp"

#include "Draw/Object.hpp"
#include "Log.h"

#include <unistd.h>

using namespace Graphics::Draw;

Animation::Animation(const Model &model, int index) :
    model(model),
    index(index){
    channels.resize(model.nodes().size());
}


Animation::~Animation(){
}


glm::mat4 Animation::getMat(const Node &node, float time){

    auto &list = channels[node.index];

    if (list.empty()){
        return node.transform.mat;
    }

    Transform tr = node.transform;
    std::vector<float> morph;
    for (int i = 0; i < list.size(); ++i){
        list[i]->apply(time, tr);
    }
    tr.applyTRS();
    return tr.mat;
}