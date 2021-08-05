#pragma once

#include "Draw/Utils/Transform.hpp"
#include "Draw/Utils/Camera.hpp"

#include "Draw/ModelData/IFaces/Animation.hpp"
#include "Draw/ModelData/IFaces/Scene.hpp"
#include "Draw/ModelData/IFaces/Model.hpp"

namespace Graphics::Draw {

class Object {
public:
    Object();
    virtual ~Object();

    Transform transform;

    void update();
    const glm::mat4 *getNodeMat(int index) const;
    const std::vector<float> *getNodeMorphWeights(int index) const;

    template<typename T>
    using Ref = std::shared_ptr<T>;

    void setModel(Ref<Model> model);
    const Ref<Model> getModel() const;

    void setCamera(Ref<Camera> camera);
    const Ref<Camera> getCamera() const;

    void setScene(int index);
    const int getScene() const;

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
    Ref<Model> _model;
    Ref<Camera> _camera;
    Ref<Scene> _scene;
    Ref<Animation> _anim;
    float _anim_time;
};

}