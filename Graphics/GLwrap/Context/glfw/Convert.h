#pragma once

#include "Context/KeyboardKey.h"
#include "Context/KeyMode.h"
#include "Context/MouseKey.h"

namespace GLwrap {

KeyboardKey getGlfwKeyboardKey(int key);
KeyMode getGlfwKeyMode(int mode);
MouseKey getGlfwMouseKey(int key);

}