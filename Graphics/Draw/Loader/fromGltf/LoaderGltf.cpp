#include "Draw/Loader/fromGltf/LoaderGltf.h"

#include <type_traits>

#include "Draw/Loader/fromGltf/gltf.h"

#include "Log.h"

using namespace Graphics::Draw;

LoaderGltf::LoaderGltf() :
    DataLoader(){
}

LoaderGltf::~LoaderGltf(){
}

void LoaderGltf::load(std::shared_ptr<Model> dst, const std::string &path, const DataIniter &initer) const {
    return const_cast<LoaderGltf *>(this)->load(dst, path, initer);
}

void LoaderGltf::load(std::shared_ptr<Model> dst, const std::string &path, const DataIniter &initer) {
    auto gltf_data = _loadGltfModel(path);
    _result = dst;
    _initer = &initer;

    for (int i = 0; i < gltf_data->accessors.size(); i++){
        auto &accessor = gltf_data->accessors[i];
        int err_count = _errors.size();
        auto gltf_buff = _loadBuffer(accessor, *gltf_data);
        _result->buffers.push_back(gltf_buff);

        for (int j = err_count; j < _errors.size(); j++){
            _errors[j] = "Buffer[" + std::to_string(j) + "]: " + _errors[j];
        }
    }

    for (int i = 0; i < gltf_data->textures.size(); i++){
        auto &texture = gltf_data->textures[i];
        int err_count = _errors.size();
        _result->textures.push_back(_loadTexture(texture, *gltf_data));

        for (int j = err_count; j < _errors.size(); j++){
            _errors[j] = "Texture[" + std::to_string(j) + "]: " + _errors[j];
        }
    }

    for (int i = 0; i < gltf_data->materials.size(); i++){
        auto gltf_material = gltf_data->materials[i];
        int err_count = _errors.size();
        _result->materials.push_back(_loadMaterial(gltf_material, *gltf_data));

        for (int j = err_count; j < _errors.size(); j++){
            _errors[j] = "Material[" + std::to_string(j) + "]: " + _errors[j];
        }
    }

    for (int i = 0; i < gltf_data->meshes.size(); i++){
        auto &gltf_mesh = gltf_data->meshes[i];
        int err_count = _errors.size();

        auto mesh = _loadMesh(gltf_mesh, *gltf_data);
        _result->meshes.push_back(mesh);

        for (int j = err_count; j < _errors.size(); j++){
            _errors[j] = "Mesh[" + std::to_string(j) + "]: " + _errors[j];
        }
    }

    if (_errors.size() > 0){
        auto log = LOG(WRN);
        log << "\n";
        for (int i = 0; i < _errors.size(); i++){
            log << _errors[i] << "\n";
        }
        _errors.clear();
    }

    _result = nullptr;
}

tinygltf::Model *LoaderGltf::_loadGltfModel(const std::string &path){
    auto model = new tinygltf::Model();
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;

    bool res = loader.LoadASCIIFromFile(model, &err, &warn, path);
    if (!warn.empty()) {
        _errors.push_back(warn);
    }

    if (!err.empty()) {
        _errors.push_back(err);
    }

    if (!res){
        _errors.push_back("failed to load glTF: " + path);
        return nullptr;
    }

    return model;
}

std::shared_ptr<Buffer> LoaderGltf::_loadBuffer(const tinygltf::Accessor &accessor,
                                                const tinygltf::Model &model){

    auto &view = model.bufferViews[accessor.bufferView];
    auto &data = model.buffers[view.buffer];

    auto elem_type = gltfConvert::getBufferElemType(accessor.componentType);
    if (elem_type == BufferElemType::Unknown){
        _errors.push_back("got unknown buffer element type (" + std::string(toString(elem_type)) + ").");
        return nullptr;
    }

    auto elem_struct = gltfConvert::getBufferElemStruct(accessor.type);
    if (elem_struct == BufferElemStruct::Unknown){
        _errors.push_back("got unknown buffer element struct (" + std::string(toString(elem_struct)) + ").");
        return nullptr;
    }

    size_t elem_size = getSize(elem_struct) * getSize(elem_type);
    size_t stride = view.byteStride == 0 ? elem_size : view.byteStride;

    auto type = gltfConvert::getBufferType(view.target);
    auto buffer = _initer->newBuffer(type, elem_type, elem_struct,
                                     accessor.count,
                                     accessor.count * elem_size,
                                     accessor.normalized);

    for (auto i = 0; i < accessor.count; i++){
        if (!buffer->write(&data.data.at(view.byteOffset + accessor.byteOffset + i * stride),
                            i * stride, elem_size)){
            _errors.push_back("writing error.");
            break;
        }
    }

    return buffer;
}

std::shared_ptr<Material> LoaderGltf::_loadMaterial(const tinygltf::Material &material,
                                                    const tinygltf::Model &model){

    auto mater = std::make_shared<Material>();
                                                 
    for (int i = 0; i < 4; i++){
        mater->base_color[i] = (float)material.pbrMetallicRoughness.baseColorFactor[i];
    }

    auto index = material.pbrMetallicRoughness.baseColorTexture.index;
    mater->base_texture = _result->textures[index];

    if (!mater->base_texture){
        _errors.push_back("texture[" + std::to_string(index) + "] is not initialized.");
    }
    
    return mater;
}

std::shared_ptr<Texture> LoaderGltf::_loadTexture(const tinygltf::Texture &gltf_tex,
                                                       const tinygltf::Model &model){
    auto &sampler = model.samplers[gltf_tex.sampler];
    auto &image = model.images[gltf_tex.source];

    auto tex = _initer->newTexture(image.width, image.height, image.component, image.bits);
    tex->write(&image.image.at(0), 0, 0, image.width, image.height);

    tex->wrap_s = gltfConvert::getTextureWrap(sampler.wrapS);
    tex->wrap_t = gltfConvert::getTextureWrap(sampler.wrapT);
    
    if (sampler.minFilter > 0){
        tex->min_filter = gltfConvert::getTextureFilter(sampler.minFilter);
    }
    
    if (sampler.magFilter > 0){
        tex->mag_filter = gltfConvert::getTextureFilter(sampler.magFilter);
    }

    return tex;
}

std::shared_ptr<Mesh> LoaderGltf::_loadMesh(const tinygltf::Mesh &mesh,
                                            const tinygltf::Model &model){
    auto res = std::make_shared<Mesh>();

    for (int i = 0; i < mesh.primitives.size(); i++){
        int err_count = _errors.size();
        auto prim = _loadPrimitive(mesh.primitives[i], model);
        res->primitives.push_back(prim);

        for (int j = err_count; j < _errors.size(); j++){
            _errors[j] = "Primitive[" + std::to_string(j) + "]: " + _errors[j];
        }
    }

    return res;
}

std::shared_ptr<Primitive> LoaderGltf::_loadPrimitive(const tinygltf::Primitive prim,
                                                      const tinygltf::Model &model){

    auto res = _initer->newPrimitive();

    res->mode = gltfConvert::getDrawMode(prim.mode);
    if (res->mode == PrimitiveDrawMode::Unknown){
        _errors.push_back("got unknown primitive draw mode (" + std::to_string(prim.mode) + ").");
        return nullptr;
    }

    if (prim.indices >= 0){
        res->indices = _result->buffers[prim.indices];
        if (!res->indices || res->indices->type != BufferType::Index){
            _errors.push_back("invalid index array type (buffer[" + std::to_string(prim.indices) + "]).");
            return nullptr;
        }
    }

    if (prim.material >= 0){
        res->material = _result->materials[prim.material];
        if (!res->material){
            _errors.push_back("material is not initialized (material[" + std::to_string(prim.material) + "]).");
            return nullptr;
        }
    }

    for (auto iter : prim.attributes){
        auto attr = gltfConvert::getAttribute(iter.first);
        if (attr == PrimitiveAttribute::Unknown){
            _errors.push_back("got unknown attribute name (" + iter.first + ").");
            continue;
        }

        auto buff = _result->buffers[iter.second];
        if (!buff || buff->type != BufferType::Vertex){
            _errors.push_back("got wrong buffer type (buffer[" + std::to_string(iter.second) + "]).");
            continue;
        }

        res->attributes[attr] = buff;
    }

    for (int i = 0; i < prim.targets.size(); i++){
        auto &list = prim.targets[i];

        std::shared_ptr<Buffer> pos;
        std::shared_ptr<Buffer> norm;
        std::shared_ptr<Buffer> tang;

        for (auto &iter : list){
            auto attr = gltfConvert::getAttribute(iter.first);
            auto buff = _result->buffers[iter.second];
            switch (attr){
                case PrimitiveAttribute::Position:
                    pos = buff;
                    break;

                case PrimitiveAttribute::Normal:
                    norm = buff;
                    break;

                case PrimitiveAttribute::Tangent:
                    tang = buff;
                    break;

                default:
                    _errors.push_back("got unknown target attribute (" + iter.first + ").");
                    continue;
            }
        }
            
        res->targets.push_back({pos, norm, tang});
    }

    res->update();
    return res;
}