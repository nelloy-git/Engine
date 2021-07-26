#include "Draw/ModelData/IFaces/AnimationChannel.hpp"

#include <cmath>
#include <algorithm>

#include "Log.h"

using namespace Graphics::Draw;

glm::vec3 AnimationChannelTranslate::get(float t, Interpolation method){
    t = t - time[0];

    // std::cout << "Min: " << time[0] << "\tMax: " << time[time.size()] << std::endl;
    // std::cout << "Period: " << time[time.size()] - time[0] << std::endl;

    t = std::fmod(t, time[time.size()] - time[0]);

    auto iter = std::lower_bound(time.begin(), time.end(), t);
    auto t2 = *iter;
    auto t1 = *(--iter);

    // std::cout << "t: " << t << "\tt1: " << t1 << "\tt2: " << t2 << std::endl;

    auto k1 = (t2 - t1) != 0 ? t / (t2 - t1) : 1;
    auto k2 = 1 - k1;
    
    // std::cout << "k1: " << k1 << "\tk2: " << k2 << std::endl;

    auto d1 = data[std::distance(time.begin(), iter)];
    auto d2 = data[std::distance(time.begin(), --iter)];

    return k1 * d1 + k2 * d2;
}

glm::quat AnimationChannelRotate::get(float t, Interpolation method){
    t = t - time[0];

    
    // std::cout << "Count: " << time.size() << std::endl;
    // std::cout << "Min: " << time[0] << "\tMax: " << time[time.size()] << std::endl;
    // std::cout << "Period: " << time[time.size()] - time[0] << std::endl;
    t = std::fmod(t, time[time.size()] - time[0]);

    auto low = std::lower_bound(time.begin(), time.end(), t);
    auto up = std::upper_bound(time.begin(), time.end(), t);
    auto t1 = *low;
    auto t2 = *up;

    auto k1 = (t2 - t1) != 0 ? (t - t1) / (t2 - t1) : 1;
    auto k2 = 1 - k1;
    auto d1 = data[std::distance(time.begin(), low)];
    auto d2 = data[std::distance(time.begin(), up)];

    return k1 * d1 + k2 * d2;
}