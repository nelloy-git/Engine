#pragma once

#include "Graphics/Model/Model.hpp"

#include "Graphics/Render/Base/Renderer.hpp"

#include "Graphics/Render/Easy/Vertex.hpp"
#include "Graphics/Render/Easy/FShader.hpp"
#include "Graphics/Render/Easy/VShader.hpp"

namespace Graphics::Render::Easy {

class Renderer : public Base::Renderer<VERT_STRUCT> {
public:
    using Model = Graphics::Model::Model<VERT_STRUCT>;

    explicit Renderer();
    Renderer(const Renderer &) = delete;
    virtual ~Renderer() = default;

    inline void setCamera(const glm::mat4 &camera) const {
        _gl_program->setUniformMat4f(_camera_loc, glm::value_ptr(camera));
    };

    void draw(const Model &model,
              const glm::mat4 &pose,
              const std::vector<float> &morph) const;
    
    static Model *newCube();

protected:
    GLint _getLoc(VShader::UniMat4);

    GLint _model_pose_loc;
    GLint _camera_loc;

};

}