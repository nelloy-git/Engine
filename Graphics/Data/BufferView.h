#pragma once

#include "GLwrap/Buffer.h"

namespace Graphics {

class BufferView {
public:
    BufferView();
    virtual ~BufferView();

    GLwrap::BufferType buffer_type;
    
};

}