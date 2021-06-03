#pragma once

#include "glad/glad.h"

#include "VBO/Object.h"
#include "VBO/utils/DataType.h"
#include "VBO/utils/UsageType.h"

namespace Graphics::VBO {

template<typename T>
class Array : public Object<T> {
public:
    Array() : Object<T>(Graphics::VBO::DataType::ARRAY){

    };

    virtual ~Array(){};

private:
};

}