#include "Draw/ModelData/IFaces/AnimCh.hpp"

#include <cmath>
#include <algorithm>

#include "Log.h"

using namespace Graphics::Draw;


AnimCh::AnimCh(Node *target,
               Buffer *time_buffer,
               Buffer *data_buffer,
               Interpolation method) :
    _target(target),
    _time(time_buffer),
    _data(data_buffer),
    _method(method){
}


AnimCh::~AnimCh(){
}


const Node *AnimCh::getTarget() const {
    return _target;
}


const Buffer *AnimCh::getTime() const {
    return _time;
}


const Buffer *AnimCh::getData() const {
    return _data;
}


Interpolation AnimCh::getMethod() const {
    return _method;
}


float AnimCh::_getNormFloat(const Buffer &buffer, size_t pos){
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

