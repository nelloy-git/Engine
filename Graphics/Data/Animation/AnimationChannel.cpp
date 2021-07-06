#include "Data/Animation/AnimationChannel.h"

#include <stdexcept>

// #include "Data/Animation/Animation.h"

using namespace Graphics;

template<>
AnimationChannel::AnimationChannel(std::shared_ptr<Node> node,
                                   std::shared_ptr<AnimationSampler<T>> sampler){

    static_assert(target == AnimationChannel::Target::Translation);
}

AnimationChannel::~AnimationChannel(){

}