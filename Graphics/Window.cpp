#include "Window.h"

#include <iostream>

using namespace Graphics;

bool Window::__glfw_inited = false;
std::unordered_map<GLFWwindow*, Window*> Window::__glfw2win;
std::mutex Window::__lock;
std::unordered_map<Window*, std::thread::id> Window::__window_thread;

Window::Window(int width, int height, std::string title) :
    __width(width),
    __height(height),
    __title(title){
    
    if (!__glfw_inited){
        __glfwInit();
    }

    __glfw_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (__glfw_window == nullptr){
        glfwTerminate();
        throw "glfwCreateWindow failed";
    }
    __glfw2win[__glfw_window] = this;

    glfwSetWindowCloseCallback(__glfw_window, [](GLFWwindow* glfw_win){
        auto win = __glfw2win[glfw_win];
        win->onClose.run();
    });

    gladLoadGL();
    glfwSwapInterval(0);
}

Window::~Window(){
    glfwDestroyWindow(__glfw_window);
}

void Window::swapBuffers(){
    glfwSwapBuffers(__glfw_window);
}

bool Window::active(){
    std::lock_guard<std::mutex> lg(__lock);

    auto winIdIt = __window_thread.find(this);
    auto thId = std::this_thread::get_id();

    if (winIdIt == __window_thread.end()){
        return false;
    }
    return winIdIt->second == thId;
}

bool Window::setActive(bool f){
    std::lock_guard<std::mutex> lg(__lock);

    auto winIdIt = __window_thread.find(this);
    auto thId = std::this_thread::get_id();

    // Window is not context for any thread.
    if (winIdIt == __window_thread.end()){
        if (f){
            glfwMakeContextCurrent(__glfw_window);
            __window_thread[this] = std::this_thread::get_id();
        }
        return true;
    }

    auto winId = winIdIt->second;
    if (thId == winId){
        if (!f){
            glfwMakeContextCurrent(__glfw_window);
            __window_thread.erase(this);
        }
        return true;
    }
    return false;
}

void Window::__glfwInit(){
    if (!glfwInit()){
        throw "glfwInit failed.";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    __glfw_inited = true;
}