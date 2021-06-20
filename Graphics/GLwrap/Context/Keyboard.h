#pragma once

#include <unordered_map>

#include "Context/KeyboardKey.h"
#include "Context/KeyMode.h"

#include "Event.h"

namespace GLwrap {

class Keyboard {
public:
    Keyboard();
    virtual ~Keyboard();

    bool isDown(KeyboardKey key);
    bool isDown(KeyboardKey key) const;

    const Event<KeyboardKey, KeyMode> onPress;
    const Event<KeyboardKey, KeyMode> onRelease;

private:
    std::unordered_map<KeyboardKey, bool> _down;
};

}