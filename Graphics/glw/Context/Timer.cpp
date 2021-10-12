#include "Context/Timer.h"

#include "GLFW/glfw3.h"

using namespace glw;

Timer::Timer(){
    _start = -1;
}

Timer::~Timer(){
}

void Timer::start(){
    _start = glfwGetTime();
    _stop = -1;
}

void Timer::stop(){
    _stop = glfwGetTime();
}

double Timer::elapsed() const {
    return _stop > 0 ? _stop - _start : glfwGetTime() - _start;
}