#include "Data/Primitive.h"

#include "Log.h"

using namespace Graphics;

Primitive::Primitive(const tinygltf::Model &model,
                     const tinygltf::Primitive &primitive,
                     const ModelBuffer &buffer){

    auto &indices_accessor = model.accessors[primitive.indices];

    auto it = buffer.indices().find(indices_accessor.bufferView);
    if (it == buffer.indices().end()){
        std::string msg = "indices buffer " + std::to_string(indices_accessor.bufferView) + " not found.";
        LOG(WRN) << msg;
        throw std::runtime_error(msg);
    }
    // auto &indices_view = model.bufferViews[indices_accessor.bufferView];
    auto indices = it->second;

    std::vector<std::pair<std::shared_ptr<GLwrap::Buffer>, std::shared_ptr<GLwrap::Accessor>>> list;
    for (auto &attr : primitive.attributes){
        auto &accessor = model.accessors[attr.second];

        int attr_loc;
        GLwrap::ComponentSize attr_size;
        GLwrap::ComponentType attr_type;
        try {
            attr_loc = glTF::getLayoutLocation(attr.first);
            attr_size = glTF::getComponentSize(accessor.type);
            attr_type = glTF::getComponentType(accessor.componentType);
        } catch (std::exception e){
            LOG(WRN) << e.what();
            continue;
        }

        auto it = buffer.data().find(accessor.bufferView);
        if (it == buffer.data().end()){
            LOG(WRN) << "data buffer "  << accessor.bufferView << " not found.";
            continue;
        }

        auto vbo = it->second;
        list.push_back({vbo,
                        std::make_shared<GLwrap::Accessor>(
                            attr_loc, attr_size, attr_type, accessor.normalized)});

        // LOG(MSG) << "\n"
        //          << "id: " << accessor.bufferView << "\n"
        //          << "buffer size: " << vbo->size << "\n"
        //          << "location: " << attr_loc << "\n"
        //          << "size: " << typeid(attr_size).name() << "\n"
        //          << "type: " << typeid(attr_type).name() << "\n";
    }

    __mode = glTF::getDrawMode(primitive.mode);
    __type = glTF::getComponentType(indices_accessor.componentType);
    __array = std::make_shared<GLwrap::Array>();
    __array->load(indices, list);
}

Primitive::~Primitive(){

}

void Primitive::draw(){
    __array->draw(__mode, __type);
}