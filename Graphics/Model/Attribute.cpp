#include "Model/Attribute.h"

using namespace Graphics;

constexpr inline const char *Model::toString(Model::Attribute attr){
    constexpr const char* map[10] = {
        "vPos",
        "vNorm",
        "vTang",
        "vTex0",
        "vTex1",
        "vCol",
        "vJoint0",
        "vJoint1",
        "vWeight0",
        "vWeight1",
    };
    
    return map[toInt(attr)];
}

constexpr inline int toInt(Model::Attribute attr){
    return static_cast<int>(attr);
}