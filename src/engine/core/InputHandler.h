#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <vector>
#include <iostream>
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum MouseButton {
    LEFT_BUTTON,
    MIDDLE_BUTTON,
    RIGHT_BUTTON
};

typedef std::function<void (const double &x, const double &y)> MousePressed;
typedef std::function<void (const double &x, const double &y)> CursorPosition;
typedef std::function<void (const int& key)> KeyPressed;
typedef std::function<void (const double &x, const double &y)> ScrollOffset;
typedef std::function<void (const unsigned int&)> CharacterCode;

class InputHandler {
private:
    static double x, y;
    static bool buttons[];
    static bool keys[];
    static std::vector<MousePressed> mousePressedListeners;
    static std::vector<CursorPosition> cursorPositionListeners;
    static std::vector<KeyPressed> keyPressedListeners;
    static std::vector<ScrollOffset> scrollOffsetListeners;
    static std::vector<CharacterCode> charactersListeners;
public:
    static void addMousePressedListner(const MousePressed &listner) {
        mousePressedListeners.push_back(listner);
    }

    static void addCursorPositionListener(const CursorPosition &listener) {
        cursorPositionListeners.push_back(listener);
    }

    static void addKeyPressedListener(const KeyPressed &listener) {
        keyPressedListeners.push_back(listener);
    }

    static void addScrollOffsetListener(const ScrollOffset &listener) {
        scrollOffsetListeners.push_back(listener);
    }

    static void addCharactersListener(const CharacterCode &listener) {
        charactersListeners.push_back(listener);
    }

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void characterCallback(GLFWwindow* window, unsigned int codepoint);
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    static void mouseButtonCallback(GLFWwindow *window, int btn, int action, int mods);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void dropCallback(GLFWwindow* window, int count, const char** paths);
};

#endif // INPUTHANDLER_H