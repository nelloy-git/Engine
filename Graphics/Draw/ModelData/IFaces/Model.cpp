#include "Draw/ModelData/IFaces/Model.hpp"

using namespace Graphics::Draw;


Animation *Model::getAnimation(int i) const {
    return _getRawPtr(_animations, i);
}


int Model::getAnimationsCount() const {
    return _animations.size();
}


Buffer *Model::getBuffer(int i) const {
    return _getRawPtr(_buffers, i);
}


int Model::getBuffersCount() const {
    return _buffers.size();
}


Texture *Model::getTexture(int i) const {
    return _getRawPtr(_textures, i);
}


int Model::getTexturesCount() const {
    return _textures.size();
}


Material *Model::getMaterial(int i) const {
    return _getRawPtr(_materials, i);
}


int Model::getMaterialsCount() const {
    return _materials.size();
}


Mesh *Model::getMesh(int i) const {
    return _getRawPtr(_meshes, i);
}


int Model::getMeshesCount() const {
    return _meshes.size();
}


Node *Model::getNode(int i) const {
    return _getRawPtr(_nodes, i);
}


int Model::getNodesCount() const {
    return _nodes.size();
}


Scene *Model::getScene(int i) const {
    return _getRawPtr(_scenes, i);
}


int Model::getScenesCount() const {
    return _scenes.size();
}