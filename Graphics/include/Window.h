#pragma once

#include <string>
#include <unordered_map>
#include <atomic>
#include <thread>
#include <mutex>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "Event.h"

namespace Graphics {

class Window {
public:
    Window(int width, int height, std::string title);
    virtual ~Window();

    void swapBuffers();

    bool active();
    bool setActive(bool f);

    std::string title();
    bool setTitle(std::string s);

    Event<> onClose;

private:
    GLFWwindow *__glfw_window;

    int __width;
    int __height;
    std::string __title;

    static bool __glfw_inited;
    static void __glfwInit();

    static std::unordered_map<GLFWwindow*, Window*> __glfw2win;

    static std::mutex __lock;
    static std::unordered_map<Window*, std::thread::id> __window_thread;
};

}