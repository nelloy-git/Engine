#include "Draw/Object.h"

using namespace Graphics::Draw;

Object::Object() :
    matrix(this, &Object::_getMatrix, nullptr),
    {

}
