#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <boost/log/trivial.hpp>
#include "exception/InitException.h"
#include <iostream>

class Window {
private:
    GLFWwindow* window;
    static void keyCallback(GLFWwindow* window,
                     int key,
                     int scancode,
                     int action,
                     int mods);
public:
    Window(int width, int height, const char* title);
    ~Window();

    int shouldClose();
    void swapBuffers();

    void update();

    void clear(float r, float g, float b);
};

#endif // WINDOW_H