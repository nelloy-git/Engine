#pragma once

#include <memory>

#include "Draw/ModelData/IFaces/Model.hpp"

namespace Graphics::Draw {

class ModelLoader {
public:
    ModelLoader() = default;
    virtual ~ModelLoader() = default;

    virtual void load(Model &dst,
                      const std::string &path,
                      std::vector<std::string> &errors) const  = 0;

protected:

    static inline Animation *addAnimation(Model &model){
        return model._addAnimation();
    };

    static inline Buffer *addBuffer(Model &model,
                                        BufferType type,
                                        BufferElemType data_type,
                                        BufferElemStruct data_struct,
                                        size_t count,
                                        size_t bytes,
                                        bool normalized){
        return model._addBuffer(type, data_type, data_struct, count, bytes, normalized);
    };
                              
    static inline Texture *addTexture(Model &model,
                                          int width,
                                          int height,
                                          int channels,
                                          int bpp){
        return model._addTexture(width, height, channels, bpp);
    };

    static inline Material *addMaterial(Model &model){
        return model._addMaterial();
    };

    static inline Mesh *addMesh(Model &model){
        return model._addMesh();
    };

    static inline Node *addNode(Model &model,
                                    const glm::mat4 &mat){
        return model._addNode(mat);
    };

    static inline Node *addNode(Model &model,
                                    const glm::vec3 &trans,
                                    const glm::quat &rot,
                                    const glm::vec3 &scale){
        return model._addNode(trans, rot, scale);
    };

    static inline Scene *addScene(Model &model){
        return model._addScene();
    };

    static inline Primitive *addPrimitive(Mesh &mesh){
        return mesh._addPrimitive();
    }

    static
};

}