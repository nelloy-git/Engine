#pragma once

#include <vector>
#include <memory>

#include "Draw/ModelData/IFaces/ModelData.h"
#include "Draw/ModelData/IFaces/Primitive.hpp"

namespace Graphics::Draw {

class Mesh : public ModelData {
friend class ModelLoader;

public:
    Mesh(const Model *model, int index) :
        ModelData(model, index){};
    virtual ~Mesh(){};

    Primitive *getPrimitive(int i){
        if (i < 0 || i >= _primitives.size()){
            return nullptr;
        }
        return _primitives[i].get();
    };

    int getPrimitivesCount(){
        return _primitives.size();
    };

    std::vector<float> morph;

protected:
    std::vector<std::unique_ptr<Primitive>> _primitives;

    virtual Primitive *_addPrimitive() = 0;
};

}