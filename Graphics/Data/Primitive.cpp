#include "Data/Primitive.h"

#include <stdexcept>
#include <algorithm>

#include "Data/ModelData.h"
#include "Log.h"

using namespace Graphics;

Primitive::Primitive(const tinygltf::Model &model,
                     const tinygltf::Primitive &primitive,
                     ModelData &data){
    
    typedef std::pair<std::shared_ptr<GLwrap::Buffer>,
                      std::shared_ptr<GLwrap::BufferAccessor>> BuffPair;

    std::vector<BuffPair> list;

    std::unordered_map<std::shared_ptr<GLwrap::BufferAccessor>, int> locations;
    for (auto &attr : primitive.attributes){
        auto &info = model.accessors[attr.second];

        int loc;
        auto buffer = _getBuffer(info, data);
        auto accessor = _getAttrAccessor(attr.first, info, loc);

        if (!buffer || !accessor){
            LOG(WRN) << "Failed creating attribute: \""
                     << attr.first << ": " << attr.second << "\"";
            continue;
        }

        locations.insert(std::make_pair(accessor, loc)); 
        list.push_back(std::make_pair(buffer, accessor));
    }

    std::sort(list.begin(), list.end(), [&locations](const BuffPair &a, const BuffPair &b) -> bool {
        return locations[a.second] < locations[b.second];
    });

    auto &indices_info = model.accessors[primitive.indices];
    auto indices = _getBuffer(indices_info, data);
    
    _vao = std::make_shared<GLwrap::Array>(indices, list);
    _vao_accessor = _getIndicesAccessor(indices_info, primitive.mode);

    if (primitive.material >= 0){
        auto &material = model.materials[primitive.material];
        _material = std::make_shared<Material>(model, material, data);
    }
}

Primitive::~Primitive(){

}

void Primitive::draw() const {
    if (_material){
        _material->apply();
    }
    _vao->bind();
    _vao_accessor->draw();
}

void Primitive::draw(){
    const_cast<const Primitive*>(this)->draw();
}

std::shared_ptr<GLwrap::BufferAccessor>
Primitive::_getAttrAccessor(const std::string &name,
                            const tinygltf::Accessor &info,
                            int &attr_loc){

    GLwrap::ComponentSize attr_size;
    GLwrap::ComponentType attr_type;

    try {
        attr_loc = glTF::getLayoutLocation(name);
        attr_size = glTF::getComponentSize(info.type);
        attr_type = glTF::getComponentType(info.componentType);
    } catch (std::exception e){
        LOG(WRN) << e.what();
        return nullptr;
    }

    return std::make_shared<GLwrap::BufferAccessor>(attr_size, attr_type,
                                                    info.normalized, (size_t)0, info.byteOffset);
}


std::shared_ptr<GLwrap::Buffer>
Primitive::_getBuffer(const tinygltf::Accessor &info, ModelData &data){
    auto view_pos = info.bufferView;
    auto view_iter = data.buffers.find(view_pos);

    if (view_iter == data.buffers.end()){
        data.buffers[view_pos] = std::make_shared<BufferView>()
    }

    if (view_pos < 0 || view_pos >= buffers.size()){
        std::string msg = "invalid buffer " + std::to_string(view_pos);
        LOG(ERR) << msg;
        throw std::runtime_error(msg);
    }

    return buffers.at(view_pos);
}

std::shared_ptr<GLwrap::ArrayAccessor>
Primitive::_getIndicesAccessor(const tinygltf::Accessor &info, int draw_mode){
    // return nullptr;
    return std::make_shared<GLwrap::ArrayAccessor>(
        glTF::getDrawMode(draw_mode),
        glTF::getComponentType(info.componentType),
        info.count,
        info.byteOffset
    );
}