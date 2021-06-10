#include "Window.h"

#include "glad/gl.h"

#include <iostream>
#include <exception>

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
        __glfw_inited = false;
        throw std::runtime_error("glfwCreateWindow failed");
    }
    __glfw2win[__glfw_window] = this;

    __initEvents();

    gladLoadGL(glfwGetProcAddress);
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
            gladLoadGL(glfwGetProcAddress);
            glfwSwapInterval(0);
            __window_thread[this] = std::this_thread::get_id();
        }
        return true;
    }

    auto winId = winIdIt->second;
    if (thId == winId){
        if (!f){
            glfwMakeContextCurrent(nullptr);
            __window_thread.erase(this);
        }
        return true;
    }
    return false;
}

bool Window::getGlParam(WindowGLparam param){
    return glIsEnabled(static_cast<GLenum>(param)) == GL_TRUE ? true : false;
}

bool Window::setGlParam(WindowGLparam param, bool f){
    if (!active()){
        return false;
    }
    
    if (f){
        glEnable(static_cast<GLenum>(param));
    } else {
        glDisable(static_cast<GLenum>(param));
    }

    return true;
}


void Window::__glfwInit(){
    if (!glfwInit()){
        throw std::runtime_error("glfwInit failed.");
    }

    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 2);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    __glfw_inited = true;
}

void Window::__initEvents(){

    glfwSetWindowCloseCallback(__glfw_window, [](GLFWwindow* glfw_win){
        auto win = __glfw2win[glfw_win];
        win->onClose.run();
    });

    glfwSetCursorEnterCallback(__glfw_window, [](GLFWwindow* glfw_win, int entered){
        auto win = __glfw2win[glfw_win];
        if (entered == GLFW_TRUE){
            win->onMouseEnter.run();
        } else {
            win->onMouseLeave.run();
        }
    });

    glfwSetCursorPosCallback(__glfw_window, [](GLFWwindow* glfw_win, double x, double y){
        auto win = __glfw2win[glfw_win];
        win->onMouseMove.run(x, y);
    });

    glfwSetMouseButtonCallback(__glfw_window, [](GLFWwindow* glfw_win, int btn, int pressed, int mode){
        auto win = __glfw2win[glfw_win];
        if (pressed == GLFW_PRESS){
            win->onMousePressed.run(btn, mode);
        } else if (pressed == GLFW_RELEASE) {
            win->onMouseReleased.run(btn, mode);
        }
    });
    
    glfwSetKeyCallback(__glfw_window, [](GLFWwindow* glfw_win, int key, int scancode, int action, int mode){
        auto win = __glfw2win[glfw_win];
        if (action == GLFW_PRESS){
            win->onKeyboardPressed.run(key, scancode, mode);
        } else if (action == GLFW_RELEASE){
            win->onKeyboardReleased.run(key, scancode, mode);
        }
    });

}