#pragma once

#include "glad/glad.h"

#include "VBO/Object.h"
#include "VBO/utils/DataType.h"
#include "VBO/utils/UsageType.h"

namespace Graphics::VBO {

class Array : public Object {
public:
    Array() : Object(Graphics::VBO::DataType::ARRAY){};
    virtual ~Array(){};

private:
};

}