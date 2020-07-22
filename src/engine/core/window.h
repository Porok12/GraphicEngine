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

class MainWindow {
private:
    SmartWindow window;
    bool cursorEnabled;
    const int MIN_WIDTH, MIN_HEIGHT;

    static std::vector<std::function<void (int, int)>> onResizeListeners;
    static void onResize(GLFWwindow* window, int width, int height);
public:
    MainWindow(int width, int height, const char* title);
    ~MainWindow();

    int getKey(int key);
    int shouldClose();
    void swapBuffers();
    void toggleCursor();
    void update();
    void clear(float r, float g, float b);
    void addOnResizeListener(std::function<void (int, int)> listener);
};

#endif // WINDOW_H