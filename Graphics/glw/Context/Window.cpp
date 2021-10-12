#include "Context/Window.h"

#include <iostream>
#include <exception>

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "Context/glfw/Convert.h"

using namespace glw;

bool Window::_glfw_inited = false;
std::unordered_map<GLFWwindow*, Window*> Window::_glfw2win;
std::mutex Window::_lock;
std::unordered_map<Window*, std::thread::id> Window::_window_thread;

Window::Window(int width, int height, std::string title) :
    _width(width),
    _height(height),
    _title(title){
    
    if (!_glfw_inited){
        _glfwInit();
    }

    _glfw_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (_glfw_window == nullptr){
        glfwTerminate();
        _glfw_inited = false;
        throw std::runtime_error("glfwCreateWindow failed");
    }
    _glfw2win[_glfw_window] = this;

    _initEvents();

    gladLoadGL(glfwGetProcAddress);
}

Window::~Window(){
    glfwDestroyWindow(_glfw_window);
}

void Window::swapBuffers(){
    glfwSwapBuffers(_glfw_window);
}

bool Window::isActive(){
    std::lock_guard<std::mutex> lg(_lock);

    auto winIdIt = _window_thread.find(this);
    auto thId = std::this_thread::get_id();

    if (winIdIt == _window_thread.end()){
        return false;
    }
    return winIdIt->second == thId;
}

bool Window::setActive(bool f){
    std::lock_guard<std::mutex> lg(_lock);

    auto winIdIt = _window_thread.find(this);
    auto thId = std::this_thread::get_id();

    // Window is not context for any thread.
    if (winIdIt == _window_thread.end()){
        if (f){
            glfwMakeContextCurrent(_glfw_window);
            gladLoadGL(glfwGetProcAddress);
            glfwSwapInterval(0);
            _window_thread[this] = std::this_thread::get_id();
        }
        return true;
    }

    auto winId = winIdIt->second;
    if (thId == winId){
        if (!f){
            glfwMakeContextCurrent(nullptr);
            _window_thread.erase(this);
        }
        return true;
    }
    return false;
}

void Window::_glfwInit(){
    if (!glfwInit()){
        throw std::runtime_error("glfwInit failed.");
    }

    glfwWindowHint(GLFW_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_VERSION_MINOR, 5);

    _glfw_inited = true;
}

void Window::_initEvents(){

    glfwSetWindowCloseCallback(_glfw_window, [](GLFWwindow* glfw_win){
        auto win = _glfw2win[glfw_win];
        win->onClose.run();
    });

    glfwSetCursorEnterCallback(_glfw_window, [](GLFWwindow* glfw_win, int entered){
        auto win = _glfw2win[glfw_win];
        if (entered == GLFW_TRUE){
            win->mouse.onEnter.run();
        } else {
            win->mouse.onLeave.run();
        }
    });

    glfwSetCursorPosCallback(_glfw_window, [](GLFWwindow* glfw_win, double x, double y){
        auto win = _glfw2win[glfw_win];
        win->mouse.onMove.run(x, y);
    });

    glfwSetMouseButtonCallback(_glfw_window, [](GLFWwindow* glfw_win, int btn, int pressed, int mode){
        auto win = _glfw2win[glfw_win];
        if (pressed == GLFW_PRESS){
            win->mouse.onPress.run(getGlfwMouseKey(btn), getGlfwKeyMode(mode));
        } else if (pressed == GLFW_RELEASE) {
            win->mouse.onRelease.run(getGlfwMouseKey(btn), getGlfwKeyMode(mode));
        } 
    });
    
    glfwSetKeyCallback(_glfw_window, [](GLFWwindow* glfw_win, int key, int scancode, int action, int mode){
        auto win = _glfw2win[glfw_win];
        if (action == GLFW_PRESS){
            win->keyboard.onPress.run(getGlfwKeyboardKey(key), getGlfwKeyMode(mode));
        } else if (action == GLFW_RELEASE){
            win->keyboard.onRelease.run(getGlfwKeyboardKey(key), getGlfwKeyMode(mode));
        }
    });

}

const std::string &Window::getTitle(){
    return _title;
}

void Window::setTitle(const std::string &s){
    _title = s;
}