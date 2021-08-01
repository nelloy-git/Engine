#include "Draw/ModelData/IFaces/AnimCh/AnimChT.hpp"

using namespace Graphics::Draw;

AnimChT::AnimChT(std::shared_ptr<Node> target,
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
            _getNormFloat(*data_buffer, 3 * i),
            _getNormFloat(*data_buffer, 3 * i + 1),
            _getNormFloat(*data_buffer, 3 * i + 2)
        );
    }
}

AnimChT::~AnimChT(){
}

void AnimChT::apply(float time, Transform &transform) const {
    switch (_method){
        case Interpolation::Linear:
            return _applyLinear(time, transform);
        
        default:
            return;
    }
}

void AnimChT::_applyLinear(float time, Transform &transform) const {
    // Out of range.
    if (time < _time_list[0] || time > _time_list.back()){
        return;
    }

    auto low = std::lower_bound(_time_list.begin(), _time_list.end(), time);
    if (low <= _time_list.begin()){
        transform.setT(_data_list[0]);
        return;
    }

    auto up = low + 1;
    if (up >= _time_list.end()){
        transform.setT(_data_list.back());
        return;
    }

    auto t1 = *low;
    auto t2 = *up;

    auto k1 = (time - t1) / (t2 - t1);
    auto k2 = 1 - k1;
    auto d1 = _data_list[std::distance(_time_list.begin(), low)];
    auto d2 = _data_list[std::distance(_time_list.begin(), up)];

    transform.setT(k1 * d1 + k2 * d2);
}