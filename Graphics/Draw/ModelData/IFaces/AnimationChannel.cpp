#include "Draw/ModelData/IFaces/AnimationChannel.hpp"

#include <cmath>
#include <algorithm>

#include "Log.h"

using namespace Graphics::Draw;

AnimationChannel::AnimationChannel(std::shared_ptr<Node> target,
                                   const Buffer &time_buffer) :
    node(target),
    time(time_buffer.count){

    node = target;
    for (int i = 0; i < time_buffer.count; ++i){
        time_buffer.read(&time[i], i * sizeof(float), sizeof(float));
    }
}

AnimationChannel::~AnimationChannel(){
}

float AnimationChannel::_getNormalized(const Buffer &buffer, size_t pos){
    switch (buffer.data_type){
    case BufferElemType::Byte:
        return std::fmax(buffer.readElement<char>(pos) / 127.0, -1.0);

    case BufferElemType::UByte:
        return buffer.readElement<unsigned char>(pos) / 255.0;

    case BufferElemType::Short:
        return std::fmax(buffer.readElement<short int>(pos) / 32767.0, -1.0);

    case BufferElemType::UShort:
        return buffer.readElement<unsigned short int>(pos) / 65535.0;

    default:
        return buffer.readElement<float>(pos);
    }
}

AnimationChannelTranslate::AnimationChannelTranslate(std::shared_ptr<Node> target,
                                                     const Buffer &time_buffer,
                                                     const Buffer &data_buffer) :
    AnimationChannel(target, time_buffer),
    data(data_buffer.count){

    for (int i = 0; i < data_buffer.count; ++i){
        data.emplace_back(
            _getNormalized(data_buffer, 3 * i),
            _getNormalized(data_buffer, 3 * i + 1),
            _getNormalized(data_buffer, 3 * i + 2)
        );
    }
}

AnimationChannelTranslate::~AnimationChannelTranslate(){
}

glm::vec3 AnimationChannelTranslate::get(float t, Interpolation method){
    t = t - time[0];
    t = std::fmod(t, time.back() - time[0]);

    auto low = std::lower_bound(time.begin(), time.end(), t);
    auto up = std::upper_bound(time.begin(), time.end(), t);

    if (low <= time.begin()){
        return data[0];
    }

    if (up >= time.end()){
        return data.back();
    }

    auto t1 = *low;
    auto t2 = *up;

    auto k1 = (t2 - t1) != 0 ? (t - t1) / (t2 - t1) : 1;
    auto k2 = 1 - k1;
    auto d1 = data[std::distance(time.begin(), low)];
    auto d2 = data[std::distance(time.begin(), up)];

    return k1 * d1 + k2 * d2;
}

AnimationChannelRotate::AnimationChannelRotate(std::shared_ptr<Node> target,
                                               const Buffer &time_buffer,
                                               const Buffer &data_buffer) :
    AnimationChannel(target, time_buffer),
    data(data_buffer.count){

    for (int i = 0; i < data_buffer.count; ++i){
        data.emplace_back(
            _getNormalized(data_buffer, 4 * i + 3),
            _getNormalized(data_buffer, 4 * i),
            _getNormalized(data_buffer, 4 * i + 1),
            _getNormalized(data_buffer, 4 * i + 2)
        );
    }
}

AnimationChannelRotate::~AnimationChannelRotate(){
}

glm::quat AnimationChannelRotate::get(float t, Interpolation method){
    t = t - time[0];
    t = std::fmod(t, time.back() - time[0]);

    auto low = std::lower_bound(time.begin(), time.end(), t);
    auto up = std::upper_bound(time.begin(), time.end(), t);

    if (low <= time.begin()){
        return data[0];
    }

    if (up >= time.end()){
        return data.back();
    }

    auto t1 = *low;
    auto t2 = *up;

    auto k1 = (t2 - t1) != 0 ? (t - t1) / (t2 - t1) : 1;
    auto k2 = 1 - k1;
    auto d1 = data[std::distance(time.begin(), low)];
    auto d2 = data[std::distance(time.begin(), up)];

    return k1 * d1 + k2 * d2;
}