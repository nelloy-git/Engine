#pragma once

#include <unordered_map>

#include "Context/KeyboardKey.h"
#include "Context/KeyMode.h"

#include "Context/Event.h"

namespace glw {

class Keyboard {
public:
    Keyboard();
    virtual ~Keyboard();

    bool isDown(KeyboardKey key);
    bool isDown(KeyboardKey key) const;

    Event<KeyboardKey, KeyMode> onPress;
    Event<KeyboardKey, KeyMode> onRelease;

private:
    std::unordered_map<KeyboardKey, bool> _down;
};

}