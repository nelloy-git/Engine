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

    void update();
    bool changed();
    const glm::mat4 &getMatrix(const Node &node) const;

    Transform transform;
    Property<std::shared_ptr<Model>, Object> model;
    Property<std::shared_ptr<Camera>, Object> camera;
    Property<int, Object> active_scene;

    float time = 0;
    Property<int, Object> active_animation;

private:

    bool _need_update = true;
    std::vector<glm::mat4> _matrices;
    void _updateNodeMatrix(Node &node, const glm::mat4 &parent_mat);

    std::shared_ptr<Model> _model;
    const std::shared_ptr<Model> &_getModel();
    void _setModel(const std::shared_ptr<Model> &model);

    std::shared_ptr<Camera> _camera;
    const std::shared_ptr<Camera> &_getCamera();
    void _setCamera(const std::shared_ptr<Camera> &camera);

    int _active_scene = 0;
    const int &_getActiveScene();
    void _setActiveScene(const int &scene);

    int _active_animation = -1;
    const int &_getActiveAnimation();
    void _setActiveAnimation(const int &anim);
    // std::map<const Node *, glm::mat4> _matrices;
};

}