#include "Graphics/Utils/Camera.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace Graphics::Draw;

inline float halfPI(){
    return 3.14159265359 / 2;
}

Camera::Camera() :
    mat(this, &Camera::_getMatrix, nullptr),
    pos(this, &Camera::_getPos, &Camera::_setPos),
    direction(this, &Camera::_getDirection, &Camera::_setDirection),
    right(this, &Camera::_getRight, nullptr),
    up(this, &Camera::_getUp, nullptr),
    yaw(this, &Camera::_getYaw, &Camera::_setYaw),
    pitch(this, &Camera::_getPitch, &Camera::_setPitch),

    perspective(this, &Camera::_getPerspective, &Camera::_setPerspective),
    fov(this, &Camera::_getFov, &Camera::_setFov),
    width(this, &Camera::_getWidth, &Camera::_setWidth),
    height(this, &Camera::_getHeight, &Camera::_setHeight),
    nearZ(this, &Camera::_getNearZ, &Camera::_setNearZ),
    farZ(this, &Camera::_getFarZ, &Camera::_setFarZ){
}

Camera::~Camera(){
}

void Camera::_update(){
    if (_view_changed){
        _right = glm::normalize(glm::cross(_direction, _up));
        _view = glm::lookAt(_pos, _pos + _direction, _up);
    }

    if (_projection_changed){
        if (_perspective){
            _projection = glm::perspectiveFov(_fov, (float)_width, (float)_height, _nearZ, _farZ);
        } else {
            _projection = glm::mat4(1.0f);
        }
    }

    _matrix = _projection * _view;
}

const glm::mat4 &Camera::_getMatrix(){
    if (_view_changed || _projection_changed){
        _update();
        _view_changed = false;
        _projection_changed = false;
    }
    return _matrix;
}

const glm::vec3 &Camera::_getPos(){
    return _pos;
}

void Camera::_setPos(const glm::vec3 &v){
    _pos = v;
    _view_changed = true;
}

const glm::vec3 &Camera::_getDirection(){
    return _direction;
}

void Camera::_setDirection(const glm::vec3 &v){
    _direction = glm::normalize(v);


    _pitch = asin(_direction.y);
    _yaw = acos(_direction.x) / cos(_pitch);

    _view_changed = true;
}

const glm::vec3 &Camera::_getRight(){
    if (_view_changed){
        _update();
        _view_changed = false;
    }
    return _right;
}

const glm::vec3 &Camera::_getUp(){
    if (_view_changed){
        _update();
        _view_changed = false;
    }
    return _up;
}

const float &Camera::_getYaw(){
    return _yaw;
}

void Camera::_setYaw(const float &a){
    _yaw = a;
    _direction = {
        cos(_yaw * cos(_pitch)),
        sin(_pitch),
        sin(_yaw * cos(_pitch))
    };
    _view_changed = true;
}

const float &Camera::_getPitch(){
    return _pitch;
}

void Camera::_setPitch(const float &a){
    _pitch = a > halfPI() ? halfPI() : a < -halfPI() ? -halfPI() : a;
    _direction = {
        cos(_yaw * cos(_pitch)),
        sin(_pitch),
        sin(_yaw * cos(_pitch))
    };
    _view_changed = true;
}

const bool &Camera::_getPerspective(){
    return _perspective;
}

void Camera::_setPerspective(const bool &f){
    _perspective = f;
    _projection_changed = true;
}

const float &Camera::_getFov(){
    return _fov;
}

void Camera::_setFov(const float &a){
    _fov = a;
    _projection_changed = true;
}

const int &Camera::_getWidth(){
    return _width;
}

void Camera::_setWidth(const int &w){
    _width = w;
    _projection_changed = true;
}

const int &Camera::_getHeight(){
    return _height;
}

void Camera::_setHeight(const int &h){
    _height = h;
    _projection_changed = true;
}

const float &Camera::_getNearZ(){
    return _nearZ;
}

void Camera::_setNearZ(const float &v){
    _nearZ = v;
    _projection_changed = true;
}

const float &Camera::_getFarZ(){
    return _farZ;
}

void Camera::_setFarZ(const float &v){
    _farZ = v;
    _projection_changed = true;
}

