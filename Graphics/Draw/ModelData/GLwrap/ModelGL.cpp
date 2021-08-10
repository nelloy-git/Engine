#include "Draw/ModelData/GLwrap/ModelGL.hpp"

#include "Draw/ModelData/GLwrap/BufferGL.hpp"
#include "Draw/ModelData/GLwrap/TextureGL.hpp"
#include "Draw/ModelData/GLwrap/PrimitiveGL.hpp"
#include "Draw/ModelData/GLwrap/MeshGL.hpp"

using namespace Graphics::Draw;

ModelGL::ModelGL() :
    Model(){
}

ModelGL::~ModelGL(){
}

Animation *ModelGL::_addAnimation(){
    return _addObj<Animation>(_animations);
}

Buffer *ModelGL::_addBuffer(BufferType type,
                               BufferElemType data_type,
                               BufferElemStruct data_struct,
                               size_t count,
                               size_t bytes,
                               bool normalized){
    return _addObj<BufferGL>(_buffers,
                             type, data_type, data_struct,
                             count, bytes, normalized);
}

Texture *ModelGL::_addTexture(int width,
                                 int height,
                                 int channels,
                                 int bpp){
    return _addObj<TextureGL>(_textures,
                              width, height, channels, bpp);
}

Material *ModelGL::_addMaterial(){
    return _addObj<Material>(_materials);
}

Mesh *ModelGL::_addMesh(){
    return _addObj<MeshGL>(_meshes);
}

Node *ModelGL::_addNode(const glm::mat4 &mat){
    return _addObj<Node>(_nodes, mat);
}

Node *ModelGL::_addNode(const glm::vec3 &trans,
                           const glm::quat &rot,
                           const glm::vec3 &scale){
    return _addObj<Node>(_nodes, trans, rot, scale);
}

Scene *ModelGL::_addScene(){
    return _addObj<Scene>(_scenes);
}