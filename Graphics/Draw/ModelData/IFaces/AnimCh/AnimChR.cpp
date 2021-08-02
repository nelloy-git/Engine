#include "Draw/ModelData/IFaces/AnimCh/AnimChR.hpp"

#include <iostream>

using namespace Graphics::Draw;

AnimChR::AnimChR(std::shared_ptr<Node> target,
                 std::shared_ptr<Buffer> time_buffer,
                 std::shared_ptr<Buffer> data_buffer) :
    AnimCh(target, time_buffer, data_buffer){
    
    // init _time_list
    _time_list.resize(time_buffer->count);
    for (int i = 0; i < _time_list.size(); ++i){
        time_buffer->read(&_time_list[i], i * sizeof(float), sizeof(float));
    }

    // init _data_list
    for (int i = 0; i < data_buffer->count; ++i){
        _data_list.emplace_back(
            _getNormFloat(*data_buffer, 4 * i + 3),
            _getNormFloat(*data_buffer, 4 * i),
            _getNormFloat(*data_buffer, 4 * i + 1),
            _getNormFloat(*data_buffer, 4 * i + 2)
        );
    }
}

AnimChR::~AnimChR(){
}

void AnimChR::apply(float time, Transform &transform) const {
    switch (_method){
        case Interpolation::Linear:
            return _applyLinear(time, transform);
        
        default:
            return;
    }
}

void AnimChR::_applyLinear(float time, Transform &transform) const {
    // Out of range.
    if (time < _time_list[0] || time > _time_list.back()){
        return;
    }

    auto upper = std::lower_bound(_time_list.begin(), _time_list.end(), time);
    if (upper >= _time_list.end()){
        transform.setR(_data_list.back());
        return;
    }

    auto lower = upper - 1;
    if (lower <= _time_list.begin()){
        transform.setR(_data_list[0]);
        return;
    }

    auto t1 = *upper;
    auto t2 = *lower;

    float k1 = (time - t1) / (t2 - t1);
    float k2 = 1 - k1;

    int p1 = std::distance(_time_list.begin(), upper);
    int p2 = p1 + 1;
    auto d1 = _data_list[p1];
    auto d2 = _data_list[p2];

    transform.setR(k1 * d1 + k2 * d2);
}