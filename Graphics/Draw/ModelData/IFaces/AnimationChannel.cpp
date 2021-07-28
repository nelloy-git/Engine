#include "Draw/ModelData/IFaces/AnimationChannel.hpp"

#include <cmath>
#include <algorithm>

#include "Log.h"

using namespace Graphics::Draw;

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