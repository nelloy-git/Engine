#pragma once

#include "Context/KeyboardKey.h"
#include "Context/KeyMode.h"
#include "Context/MouseKey.h"

namespace glw {

KeyboardKey getGlfwKeyboardKey(int key);
KeyMode getGlfwKeyMode(int mode);
MouseKey getGlfwMouseKey(int key);

}