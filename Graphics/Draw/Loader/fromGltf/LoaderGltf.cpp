#include "Draw/Loader/fromGltf/LoaderGltf.h"

#include <type_traits>

#include "3rdparty/tinygltf/tiny_gltf.h"

#include "Draw/Loader/fromGltf/gltf.h"

#include "Log.h"

using namespace Graphics::Draw;

LoaderGltf::LoaderGltf() :
    DataLoader(){
}

LoaderGltf::~LoaderGltf(){
}

void LoaderGltf::load(std::shared_ptr<Model> dst, const std::string &path, const DataIniter &initer){
    auto gltf_model = _loadGltfModel(path);
    _result = dst;
    _initer = &initer;

    _result->buffers = _iterate(gltf_model->accessors, *gltf_model, &LoaderGltf::_loadBuffer);
    _result->textures = _iterate(gltf_model->textures, *gltf_model, &LoaderGltf::_loadTexture);
    _result->materials = _iterate(gltf_model->materials, *gltf_model, &LoaderGltf::_loadMaterial);
    _result->meshes = _iterate(gltf_model->meshes, *gltf_model, &LoaderGltf::_loadMesh);
    _result->nodes = _iterate(gltf_model->nodes, *gltf_model, &LoaderGltf::_loadNode);
    _linkNodes(*gltf_model);
    _result->scenes = _iterate(gltf_model->scenes, *gltf_model, &LoaderGltf::_loadScene);

    for (int i = 0; i < gltf_model->nodes.size(); i++){
        auto &gltf_node = gltf_model->nodes[i];
        auto node = _result->nodes[i];
        node->index = i;

        if (node->children.size() > 0){
            continue;
        }

        for (int j = 0; j < gltf_node.children.size(); j++){
            auto child = _result->nodes[gltf_node.children[j]];
            node->children.push_back(child);

            if (child->parent){
                _errors.push_back("Node[" + std::to_string(j) + "] can have only one parent.");
                continue;
            }

            child->parent = node;
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
        _errors.push_back("got unknown buffer element type (" + toString(elem_type) + ").");
        return nullptr;
    }

    auto elem_struct = gltfConvert::getBufferElemStruct(accessor.type);
    if (elem_struct == BufferElemStruct::Unknown){
        _errors.push_back("got unknown buffer element struct (" + toString(elem_struct) + ").");
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

std::shared_ptr<Mesh> LoaderGltf::_loadMesh(const tinygltf::Mesh &gltf_mesh,
                                            const tinygltf::Model &gltf_model){
    auto mesh = std::make_shared<Mesh>();
    mesh->primitives = _iterate(gltf_mesh.primitives, gltf_model, &LoaderGltf::_loadPrimitive);

    return mesh;
}

std::shared_ptr<Primitive> LoaderGltf::_loadPrimitive(const tinygltf::Primitive &gltf_prim,
                                                      const tinygltf::Model &gltf_model){

    auto res = _initer->newPrimitive();

    res->mode = gltfConvert::getDrawMode(gltf_prim.mode);
    if (res->mode == PrimitiveDrawMode::Unknown){
        _errors.push_back("got unknown primitive draw mode (" + std::to_string(gltf_prim.mode) + ").");
        return nullptr;
    }

    if (gltf_prim.indices >= 0){
        res->indices = _result->buffers[gltf_prim.indices];
        if (!res->indices || res->indices->type != BufferType::Index){
            _errors.push_back("invalid index array type (buffer[" + std::to_string(gltf_prim.indices) + "]).");
            return nullptr;
        }
    }

    if (gltf_prim.material >= 0){
        res->material = _result->materials[gltf_prim.material];
        if (!res->material){
            _errors.push_back("material is not initialized (material[" + std::to_string(gltf_prim.material) + "]).");
            return nullptr;
        }
    }

    for (auto iter : gltf_prim.attributes){
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

    for (int i = 0; i < gltf_prim.targets.size(); i++){
        auto &list = gltf_prim.targets[i];

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
            
        res->morph_targets.push_back({pos, norm, tang});
    }

    res->init();
    return res;
}

std::shared_ptr<Node> LoaderGltf::_loadNode(const tinygltf::Node &gltf_node,
                                            const tinygltf::Model &gltf_model){
    std::shared_ptr<Node> node;

    if (gltf_node.matrix.size() != 0){
        if (gltf_node.matrix.size() == 16){
            glm::mat4 mat;
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 4; j++){
                    mat[i][j] = gltf_node.matrix[i * 4 + j];
                }
            }
            node = _initer->newNode(mat);
        } else {
            _errors.push_back("wrong matrix size.");
        }
    } else {
        glm::vec3 scale(1.f);
        if (gltf_node.scale.size() == 3){
            scale = {
                gltf_node.scale[0],
                gltf_node.scale[1],
                gltf_node.scale[2]
            };
        }

        glm::quat rot = {1.f, 0.f, 0.f, 0.f};
        if (gltf_node.rotation.size() == 4){
            rot = {
                (float)gltf_node.rotation[3], 
                (float)gltf_node.rotation[0], 
                (float)gltf_node.rotation[1], 
                (float)gltf_node.rotation[2]
            };
        }

        glm::vec3 trans(0.f);
        if (gltf_node.translation.size() == 3){
            trans = {
                gltf_node.translation[0],
                gltf_node.translation[1],
                gltf_node.translation[2]};
        }

        node = _initer->newNode(trans, rot, scale);
    }

    if (gltf_node.mesh >= 0){
        node->mesh = _result->meshes[gltf_node.mesh];
    }
    return node;
}

void LoaderGltf::_linkNodes(const tinygltf::Model &gltf_model){
    for (int i = 0; i < gltf_model.nodes.size(); i++){
        auto &gltf_node = gltf_model.nodes[i];
        auto node = _result->nodes[i];

        if (node->children.size() > 0){
            continue;
        }

        for (int j = 0; j < gltf_node.children.size(); j++){
            auto child = _result->nodes[gltf_node.children[j]];
            node->children.push_back(child);

            if (child->parent){
                _errors.push_back("Node[" + std::to_string(j) + "] can have only one parent.");
                continue;
            }

            child->parent = node;
        }
    }
}

std::shared_ptr<Scene> LoaderGltf::_loadScene(const tinygltf::Scene &gltf_scene,
                                              const tinygltf::Model &gltf_model){
    auto scene = _initer->newScene();

    for (int i = 0; i < gltf_scene.nodes.size(); i++){
        int node_pos = gltf_scene.nodes[i];
        scene->nodes.push_back(_result->nodes[node_pos]);
    }

    return scene;
}