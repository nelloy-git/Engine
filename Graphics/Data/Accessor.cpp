#include "Data/Accessor.h"

#include <stdexcept>

#include "Data/ModelData.h"

using namespace Graphics;

Accessor::Accessor(const tinygltf::Accessor &acc,
                   ModelData &data) :
    count(acc.count){
    
    GLwrap::ComponentSize attr_size;
    GLwrap::ComponentType attr_type;

    try {
        attr_size = glTF::getComponentSize(acc.type);
        attr_type = glTF::getComponentType(acc.componentType);
    } catch (std::exception e){
        std::string what("Can not create Accessor. ");
        what += e.what();
        throw std::invalid_argument(what);
    }

    accessor = std::make_shared<GLwrap::BufferAccessor>(
                    attr_size, attr_type, acc.normalized,
                    0, acc.byteOffset);
    view = data.getBufferView(acc.bufferView);
}

Accessor::~Accessor(){
    
}