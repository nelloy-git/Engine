#include "Context/Mouse.h"

using namespace glw;

Mouse::Mouse(){
    onPress.add([this](MouseKey key, KeyMode mode){
        _down[key] = true;
    });

    onRelease.add([this](MouseKey key, KeyMode mode){
        _down[key] = false;
    });
}

Mouse::~Mouse(){
}

bool Mouse::isDown(MouseKey key){
    auto it = _down.find(key);
    if (it == _down.end()){
        return false;
    }
    return it->second;
}

bool Mouse::isDown(MouseKey key) const{
    return const_cast<Mouse *>(this)->isDown(key);
}