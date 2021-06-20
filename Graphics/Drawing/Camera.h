#pragma once

#include "glm/glm.hpp"

#include "Property.h"

namespace Graphics {

class Camera {
public:
    Camera();
    virtual ~Camera();

    const glm::mat4 &matrix();
    const glm::vec3 &right_old();

    Property<glm::vec3, Camera> pos;
    Property<glm::vec3, Camera> direction;
    const Property<glm::vec3, Camera> right;
    Property<float, Camera> yaw;
    Property<float, Camera> pitch;

    Property<bool, Camera> perspective;
    Property<float, Camera> fov;
    Property<int, Camera> width;
    Property<int, Camera> height;
    Property<float, Camera> nearZ;
    Property<float, Camera> farZ;

private:
    void _update();

    glm::mat4 _view = glm::mat4(1.0f);
    bool _view_changed = true;

    glm::mat4 _projection = glm::mat4(1.0f);
    bool _projection_changed = true;

    glm::mat4 _matrix = glm::mat4(1.0f);

    const glm::vec3 &_getPos();
    void _setPos(const glm::vec3 &v);
    glm::vec3 _pos = {0, 0, 0};

    const glm::vec3 &_getDirection();
    void _setDirection(const glm::vec3 &v);
    glm::vec3 _direction = {1, 0, 0};
    glm::vec3 _right = {0, 0, 1};
    glm::vec3 _up = {0, 1, 0};

    const float &_getYaw();
    void _setYaw(const float &a);
    float _yaw = 0;

    const float &_getPitch();
    void _setPitch(const float &a);
    float _pitch = 0;

    const bool &_getPerspective();
    void _setPerspective(const bool &f);
    bool _perspective = true;

    const float &_getFov();
    void _setFov(const float &a);
    float _fov = 3.14159265359 / 2;

    const int &_getWidth();
    void _setWidth(const int &w);
    int _width = 800;
    
    const int &_getHeight();
    void _setHeight(const int &h);
    int _height = 600;

    const float &_getNearZ();
    void _setNearZ(const float &z);
    float _nearZ = 0.1;

    const float &_getFarZ();
    void _setFarZ(const float &z);
    float _farZ = 100;
};

}