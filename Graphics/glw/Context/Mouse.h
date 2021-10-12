#pragma once

#include <unordered_map>

#include "Context/MouseKey.h"
#include "Context/KeyMode.h"

#include "Context/Event.h"

namespace glw{
    
class Mouse {
public:
    Mouse();
    virtual ~Mouse();

    double x();
    double y();

    bool isDown(MouseKey key);
    bool isDown(MouseKey key) const;

    const Event<MouseKey, KeyMode> onPress;
    const Event<MouseKey, KeyMode> onRelease;
    const Event<double, double> onMove;
    const Event<> onEnter;
    const Event<> onLeave;

private:
    double _x;
    double _y;
    std::unordered_map<MouseKey, bool> _down;
};

}
