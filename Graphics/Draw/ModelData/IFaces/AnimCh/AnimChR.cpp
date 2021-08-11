#include "Draw/ModelData/IFaces/AnimCh/AnimChR.hpp"

#include <iostream>

using namespace Graphics::Draw;

AnimChR::AnimChR(const Node &target,
                 const Buffer &time_buffer,
                 const Buffer &data_buffer) :
    AnimCh(target, time_buffer, data_buffer){
    
    // init _time_list
    _time_list.resize(time_buffer.count);
    for (int i = 0; i < _time_list.size(); ++i){
        time_buffer.read(&_time_list[i], i * sizeof(float), sizeof(float));
    }

    // init _data_list
    for (int i = 0; i < data_buffer.count; ++i){
        _data_list.emplace_back(
            _getNormFloat(data_buffer, 4 * i + 3),
            _getNormFloat(data_buffer, 4 * i),
            _getNormFloat(data_buffer, 4 * i + 1),
            _getNormFloat(data_buffer, 4 * i + 2)
        );
    }
}

AnimChR::~AnimChR(){
}

void AnimChR::apply(float time, Transform &transform, std::vector<float> &morph) const {
    switch (_method){
        case Interpolation::Linear:
            return _applyLinear(time, transform);
        
        default:
            return;
    }
}

void AnimChR::_applyLinear(float time, Transform &transform) const {
    
    if (time <= _time_list[0]){
        transform.setR(_data_list[0]);
        return;
    }

    if (time >= _time_list.back()){
        transform.setR(_data_list.back());
        return;
    }

    auto up = std::lower_bound(_time_list.begin(), _time_list.end(), time);
    if (up == _time_list.end()){
        transform.setR(_data_list.back());
        return;
    }

    auto low = up - 1;

    auto low_t = *low;
    auto up_t = *up;

    float up_k = (time - low_t) / (up_t - low_t);
    float low_k = 1 - up_k;

    int low_p = std::distance(_time_list.begin(), low);
    int up_p = low_p + 1;

    auto low_d = _data_list[low_p];
    auto up_d = _data_list[up_p];

    transform.setR(glm::slerp(low_d, up_d, up_k));
}