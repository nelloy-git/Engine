#pragma once

namespace Graphics::Model {

class Model;

class Data {
public:
    Data(const Model *model, int index) :
        model(model),
        index(index){
    };
    virtual ~Data() = 0;

    const Model *model;
    const int index;
};

inline Data::~Data(){
};

}