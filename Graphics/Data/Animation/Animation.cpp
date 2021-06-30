#include "Data/Animation/Animation.h"

using namespace Graphics;

Animation::Animation(const tinygltf::Animation &anim,
                     ModelData &data){

    for (int i = 0; i < anim.samplers.size(); i++){
        samplers.push_back(std::make_shared<AnimationSampler>(anim.samplers[i], *this, data));
    }
    
    for (int i = 0; i < anim.channels.size(); i++){
        channels.push_back(std::make_shared<AnimationChannel>(anim.channels[i], *this, data));
    }
}

Animation::~Animation(){

}