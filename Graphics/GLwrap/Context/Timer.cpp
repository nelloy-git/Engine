#include "Context/Timer.h"

#include "GLFW/glfw3.h"

using namespace GLwrap;

Timer::Timer(){
    _start = -1;
}

Timer::~Timer(){
}

void Timer::start(){
    _start = glfwGetTime();
}

void Timer::stop(){
    _start = -1;
}

double Timer::elapsed(){
    return const_cast<const Timer*>(this)->elapsed();
}

double Timer::elapsed() const{
    return _start > 0 ? glfwGetTime() - _start : -1;
}