#include "Draw/ModelData/IFaces/Model.hpp"

using namespace Graphics::Draw;

template<typename T>
using ref = std::shared_ptr<T>;

Model::~Model(){
}

const std::vector<ref<Animation>> &Model::animations() const {
    return _animations;
}

const std::vector<ref<Buffer>> &Model::buffers() const {
    return _buffers;
}

const std::vector<ref<Scene>> &Model::scenes() const {
    return _scenes;
}

const std::vector<ref<Node>> &Model::nodes() const {
    return _nodes;
}

const std::vector<ref<Mesh>> &Model::meshes() const {
    return _meshes;
}

const std::vector<ref<Material>> &Model::materials() const {
    return _materials;
}

const std::vector<ref<Texture>> &Model::textures() const {
    return _textures;
}