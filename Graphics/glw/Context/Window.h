#pragma once

#include <string>
#include <unordered_map>
#include <atomic>
#include <thread>
#include <mutex>

#include "Context/Keyboard.h"
#include "Context/Mouse.h"

#include "Context/Event.h"

class GLFWwindow;

namespace glw {


class Window {

public:
    Window(int width, int height, std::string title);
    virtual ~Window();

    void swapBuffers();

    bool isActive();
    bool setActive(bool f);

    const std::string &getTitle();
    void setTitle(const std::string &s);

    Event<> onClose;

    const Keyboard keyboard;
    const Mouse mouse;

private:
    void _initEvents();

    GLFWwindow *_glfw_window;

    int _width;
    int _height;
    std::string _title;

    static bool _glfw_inited;
    static void _glfwInit();

    static std::unordered_map<GLFWwindow*, Window*> _glfw2win;

    static std::mutex _lock;
    static std::unordered_map<Window*, std::thread::id> _window_thread;
};

}