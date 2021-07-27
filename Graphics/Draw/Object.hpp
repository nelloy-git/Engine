#pragma once

#include <optional>
#include <unordered_map>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Draw/Utils/Transform.hpp"
#include "Draw/Utils/Camera.hpp"
#include "Draw/ModelData/IFaces/Model.hpp"
#include "Property.hpp"

namespace Graphics::Draw {

class Object {
public:
    Object();
    virtual ~Object();

    bool update();
    // bool changed();
    // const glm::mat4 &getMatrix(const Node &node) const;

    Transform transform;
    const Transform &getNodeTransform(const Node &node) const;

    void setModel(std::shared_ptr<Model> model);
    std::shared_ptr<Model> getModel() const;

    void setCamera(std::shared_ptr<Camera> camera);
    std::shared_ptr<Camera> getCamera() const;

    void setScene(int index);
    std::shared_ptr<Scene> getScene() const;

    void setAnimation(float time, int index);
    std::pair<float, int> getAnimation() const;

    // Property<std::shared_ptr<Model>, Object> model;
    // Property<std::shared_ptr<Camera>, Object> camera;
    // Property<int, Object> active_scene;

    // float time = 0;
    // Property<int, Object> active_animation;

private:

    void _updateModel();
    void _updateCamera();
    void _updateScene();
    void _updateAnimation();
    void _updateNodeTransform(Node &node, const glm::mat4 &parent_mat);

    bool _node_transforms_changed;
    std::vector<Transform> _node_transforms;

    bool _model_changed;
    std::shared_ptr<Model> _model;

    bool _camera_changed;
    std::shared_ptr<Camera> _camera;

    bool _scene_changed;
    int _scene_index;
    std::shared_ptr<Scene> _scene;

    bool _anim_changed;
    float _anim_time;
    int _anim_index;
    std::shared_ptr<Animation> _anim;

    // const std::shared_ptr<Model> &_getModel();
    // void _setModel(const std::shared_ptr<Model> &model);

    // const std::shared_ptr<Camera> &_getCamera();
    // void _setCamera(const std::shared_ptr<Camera> &camera);

    // int _active_scene = 0;
    // const int &_getActiveScene();
    // void _setActiveScene(const int &scene);

    // int _active_animation = -1;
    // const int &_getActiveAnimation();
    // void _setActiveAnimation(const int &anim);
    // std::map<const Node *, glm::mat4> _matrices;
};

}