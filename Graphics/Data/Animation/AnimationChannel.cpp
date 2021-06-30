#include "Data/Animation/AnimationChannel.h"

#include <stdexcept>

#include "Data/ModelData.h"
#include "Data/Animation/Animation.h"

using namespace Graphics;

AnimationChannel::AnimationChannel(const tinygltf::AnimationChannel &channel,
                                   Animation &anim, ModelData &data){
    auto sampler_pos = channel.sampler;
    sampler = anim.samplers.at(sampler_pos);
    node = data.getNode(channel.target_node);

    auto &path = channel.target_path;
    if (path == "translation"){
        target = Target::Translation;
    } else if (path == "rotation"){
        target = Target::Rotation;
    } else if (path == "scale"){
        target = Target::Scale;
    } else if (path == "weights"){
        target = Target::Weight;
    } else {
        throw std::invalid_argument("Can not create AnimationChannel. Unknown node target.");
    }
}

AnimationChannel::~AnimationChannel(){

}