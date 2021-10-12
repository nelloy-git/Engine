#include "Context/Keyboard.h"

using namespace glw;

Keyboard::Keyboard(){
    onPress.add([this](KeyboardKey key, KeyMode mode){
        _down[key] = true;
    });

    onRelease.add([this](KeyboardKey key, KeyMode mode){
        _down[key] = false;
    });
}

Keyboard::~Keyboard(){
}

bool Keyboard::isDown(KeyboardKey key){
    auto it = _down.find(key);
    if (it == _down.end()){
        return false;
    }
    return it->second;
}

bool Keyboard::isDown(KeyboardKey key) const{
    return const_cast<Keyboard *>(this)->isDown(key);
}