#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Property.hpp"

namespace Graphics::Draw {

class Transform {
public:
    Transform();
    virtual ~Transform();

    const Property<glm::mat4, Transform> matrix;
    Property<glm::vec3, Transform> translation;
    Property<glm::quat, Transform> rotation;
    Property<glm::vec3, Transform> scale;

private:
    bool _need_update = false;
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