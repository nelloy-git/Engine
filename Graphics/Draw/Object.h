#pragma once

#include <optional>
#include <unordered_map>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Draw/Model.h"
#include "Property.h"

namespace Graphics::Draw {

class Object {
public:
    Object();
    virtual ~Object();

    const Property<glm::mat4, Object> matrix;
    Property<glm::vec3, Object> translation;
    Property<glm::quat, Object> rotation;
    Property<glm::vec3, Object> scale;

    Property<std::shared_ptr<Model>, Object> model;
    // Property

private:
    bool _matrix_need_update = false;
    glm::mat4 _matrix;
    const glm::mat4 &_getMatrix();

    glm::vec3 _trans;
    const glm::vec3 &_getTranslation();
    void _setTranslation(const glm::vec3 &translation);

    glm::quat _rot;
    const glm::quat &_getRotation();
    void _setRotation(const glm::quat &rotation);

    glm::vec3 _scale;
    const glm::vec3 &_getScale();
    void _setScale(const glm::vec3 &scale);
};

}