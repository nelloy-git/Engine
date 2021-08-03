#pragma once

#include "Draw/Utils/Transform.hpp"

namespace Graphics::Draw {

class Object {
public:
    Object();
    virtual ~Object();

    Transform transform;

};

}