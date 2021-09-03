#pragma once

#include "Graphics/Utils/Transform.hpp"
#include "Graphics/Utils/Camera.hpp"

#include "Graphics/ModelData/IFaces/Animation.hpp"
#include "Graphics/ModelData/IFaces/Scene.hpp"
#include "Graphics/ModelData/IFaces/Model.hpp"

namespace Graphics::Draw {

class Object {
public:
    Object();
    virtual ~Object();

    Transform transform;

    void update();
    const glm::mat4 *getNodeMat(int index) const;
    const std::vector<float> *getNodeMorph(int index) const;

    void setModel(Model *model);
    Model *getModel();
    const Model *getModel() const;

    void setCamera(Camera *camera);
    Camera *getCamera();
    const Camera *getCamera() const;

    void setScene(int index);
    int getScene() const;

    void setAnimation(int index);
    const int getAnimation() const ;

    void setAnimationTime(float time);
    const float getAnimationTime() const;

    // TODO Animation mixing.

private:
    void _updateNode(const Node &node, const glm::mat4 &root_mat);

    bool _changed = true;

    glm::mat4 _model_mat;
    std::vector<glm::mat4> _node_mats;
    std::vector<std::vector<float>> _node_weights;
    Model *_model;
    Camera *_camera;
    Scene *_scene;
    Animation *_anim;
    float _anim_time;
};

}