#pragma once

namespace Graphics::Draw {

class Model;

class ModelData {
public:
    ModelData(const Model *model, int index) :
        model(model),
        index(index){
    };
    virtual ~ModelData() = 0;

    const Model *model;
    const int index;
};

inline ModelData::~ModelData(){
};

}