#include "Draw/ModelData/GLwrap/ModelGL.hpp"

#include "Draw/ModelData/GLwrap/BufferGL.hpp"
#include "Draw/ModelData/GLwrap/TextureGL.hpp"
#include "Draw/ModelData/GLwrap/PrimitiveGL.hpp"
#include "Draw/ModelData/GLwrap/MeshGL.hpp"

using namespace Graphics::Draw;

template<typename T>
using ref = std::shared_ptr<T>;

ModelGL::ModelGL() :
    Model(){
}

ModelGL::~ModelGL(){
}

ref<Animation> ModelGL::addAnimation(){
    return _addObj<Animation>(_animations);
}

ref<Buffer> ModelGL::addBuffer(BufferType type,
                               BufferElemType data_type,
                               BufferElemStruct data_struct,
                               size_t count,
                               size_t bytes,
                               bool normalized){
    return _addObj<BufferGL>(_buffers,
                            type, data_type, data_struct,
                            count, bytes, normalized);
}

ref<Texture> ModelGL::addTexture(int width,
                                 int height,
                                 int channels,
                                 int bpp){
    return _addObj<TextureGL>(_textures,
                              width, height, channels, bpp);
}

ref<Material> ModelGL::addMaterial(){
    return _addObj<Material>(_materials);
}

ref<Mesh> ModelGL::addMesh(){
    return _addObj<MeshGL>(_meshes);
}

ref<Node> ModelGL::addNode(const glm::mat4 &mat){
    return _addObj<Node>(_nodes, mat);
}

ref<Node> ModelGL::addNode(const glm::vec3 &trans,
                           const glm::quat &rot,
                           const glm::vec3 &scale){
    return _addObj<Node>(_nodes, trans, rot, scale);
}

ref<Scene> ModelGL::addScene(){
    return _addObj<Scene>(_scenes);
}