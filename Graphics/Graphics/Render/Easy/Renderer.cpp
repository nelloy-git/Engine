#include "Graphics/Render/Easy/Renderer.hpp"

#include "Graphics/Model/Mesh.hpp"
#include "Graphics/Model/Node.hpp"

using namespace Graphics::Render::Easy;

using UniMat4 = VShader::UniMat4;
using Mesh = Graphics::Model::Mesh<VERT_STRUCT>;
using Node = Graphics::Model::Node<VERT_STRUCT>;

Renderer::Renderer() :
    Base::Renderer<VERT_STRUCT>(VShader(), FShader()),
    _model_pose_loc(_getLoc(UniMat4::ModelPose)),
    _camera_loc(_getLoc(UniMat4::Camera)){
}

void Renderer::draw(const Model &model,
                    const glm::mat4 &pose,
                    const std::vector<float> &morph) const {
    _gl_program->setUniformMat4f(_model_pose_loc, glm::value_ptr(pose));

    // for (int i = 0; i < model.nodes.size(); ++i){
    //     auto &node = model.nodes[i];
    //     auto mesh = node.mesh;

    //     if (!mesh){
    //         continue;
    //     }
        
    //     for (int j = 0; j < mesh->primitives.size(); ++j){
    //         auto &prim = mesh->primitives[i];
    //         prim.draw();
    //     }
    // }

    for (int i = 0; i < model.meshes.size(); ++i){
        auto &mesh = model.meshes[i];
        for (int j = 0; j < mesh.primitives.size(); ++j){
            auto &prim = mesh.primitives[j];
            prim.draw();
        }
    }

    // prim.draw();
}

Renderer::Model *Renderer::newCube(){
    static const std::vector<Vertex> cube_data = {
        {.pos = {0, 0, 0}, .color = {{0, 1, 0, 1}}},
        {.pos = {0, 0, 1}, .color = {{0, 1, 0, 1}}},
        {.pos = {0, 1, 0}, .color = {{0, 1, 0, 1}}},
        {.pos = {0, 1, 1}, .color = {{0, 1, 0, 1}}},
        {.pos = {1, 0, 0}, .color = {{0, 1, 0, 1}}},
        {.pos = {1, 0, 1}, .color = {{0, 1, 0, 1}}},
        {.pos = {1, 1, 0}, .color = {{0, 1, 0, 1}}},
        {.pos = {1, 1, 1}, .color = {{0, 1, 0, 1}}},
    };

    static const std::vector<unsigned int> cube_indices = {
        0, 2, 3,
        0, 1, 3,
        0, 2, 6,
        0, 6, 4,
        0, 1, 5,
        0, 5, 4,
        7, 6, 4,
        7, 4, 5,
        7, 2, 6,
        7, 3, 2,
        7, 1, 5,
        7, 3, 1
    };

    auto model = new Model();
    model->meshes.emplace_back();
    model->meshes.back().primitives.emplace_back(cube_data, &cube_indices);

    glm::vec3 t = {0, 0, 0};
    glm::quat r = {1, 0, 0, 0};
    glm::vec3 s = {1, 1, 1};
    model->nodes.emplace_back(t, r, s);
    model->nodes.back().mesh = &model->meshes.back();
    // model->meshes.emplace_back(model, model->meshes.size());
    // model->meshes.back().primitives.emplace_back<Primitive>(cube_data, &cube_indices);

    return model;
}

GLint Renderer::_getLoc(UniMat4 e){
    return _gl_program->getUniformLoc(VShader::getName(e));
}