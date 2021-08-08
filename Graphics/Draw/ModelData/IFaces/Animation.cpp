#include "Draw/ModelData/IFaces/Animation.hpp"

#include "Draw/Object.hpp"
#include "Log.h"

using namespace Graphics::Draw;

Animation::Animation(const Model &model, int index) :
    model(model),
    index(index){
    channels.resize(model.nodes().size());
}


Animation::~Animation(){
}


void Animation::getMat(const Node &node, float time, glm::mat4 *mat, std::vector<float> *morph){

    auto &list = channels[node.index];
    *morph = node.mesh ? node.mesh->morph : std::vector<float>();

    if (list.empty()){
        *mat = node.transform.mat;
        return;
    }

    Transform tr = node.transform;
    for (int i = 0; i < list.size(); ++i){
        list[i]->apply(time, tr, *morph);
    }
    tr.applyTRS();
    *mat = tr.mat;
    return;
}