#pragma once

#include <iostream>
#include <string>

#include "Property.hpp"

class Example {
public:
    Property<std::string, Example> normal;
    const Property<std::string, Example> readonly;

    Example() :
        normal(this, _getNormal, _setNormal),
        readonly(this, _getReadonly){
    };

    virtual ~Example(){};

private:
    std::string _normal_val;
    const std::string &_getNormal(){
        std::cout << "Read normal " << _normal_val;
        return _normal_val;
    };

    void _setNormal(const std::string &val){
        std::cout << "Write normal " << val;
        _normal_val = val;
    };

    std::string _readonly_val;
    const std::string &_getReadonly(){
        std::cout << "Read readonly " << _normal_val;
        return _normal_val;
    };
};