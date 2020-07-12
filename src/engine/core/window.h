#ifndef WINDOW_H
#define WINDOW_H

#include <boost/log/trivial.hpp>
#include <iostream>
#include <memory>
#include "exception/InitException.h"
#include "InputHandler.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct DestroyGLFW {
    void operator()(GLFWwindow* ptr) {
        glfwDestroyWindow(ptr);
    }
};

typedef std::unique_ptr<GLFWwindow, DestroyGLFW> SmartWindow;

class Window {
private:
    SmartWindow window;
public:
    Window(int width, int height, const char* title);
    ~Window();

    int shouldClose();
    void swapBuffers();
    void getCursor(double &x, double &y);
    int getKey(int key);

    bool mouseButtonLeft();

    void update();

    void clear(float r, float g, float b);
};

#endif // WINDOW_H