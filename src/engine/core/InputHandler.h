#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <vector>
#include <iostream>
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum MouseButtons {
    LEFT_BUTTON,
    MIDDLE_BUTTON,
    RIGHT_BUTTON
};

//TODO: Refactor
typedef std::function<void (const double &x, const double &y)> MouseButton;
typedef std::function<void (const double &x, const double &y)> MousePressed;
typedef std::function<void (const double &x, const double &y)> MouseRelease;
typedef std::function<void (const double &x, const double &y)> CursorPosition;
typedef std::function<void (const double &x, const double &y)> CursorOffset;
typedef std::function<void (const int& key)> KeyPressed;
typedef std::function<void (const double &x, const double &y)> ScrollOffset;
typedef std::function<void (const unsigned int&)> CharacterCode;

class InputHandler {
private:
    static bool updated;
    static double x, y;
    static bool buttons[];
    static bool keys[];
    static std::vector<MouseButton> mouseButtonListeners;
    static std::vector<MousePressed> mousePressedListeners;
    static std::vector<MouseRelease> mouseReleaseListeners;
    static std::vector<CursorPosition> cursorPositionListeners;
    static std::vector<CursorPosition> cursorOffsetListeners;
    static std::vector<KeyPressed> keyPressedListeners;
    static std::vector<ScrollOffset> scrollOffsetListeners;
    static std::vector<CharacterCode> charactersListeners;
public:
    static void addMousePressedListner(const MousePressed &listner) {
        mousePressedListeners.push_back(listner);
    }

    static void addMouseReleaseListner(const MouseRelease &listner) {
        mouseReleaseListeners.push_back(listner);
    }

    static void addMouseButtonListner(const MouseButton &listner) {
        mouseButtonListeners.push_back(listner);
    }

    static void addCursorPositionListener(const CursorPosition &listener) {
        cursorPositionListeners.push_back(listener);
    }

    static void addCursorOffsetListener(const CursorOffset &listener) {
        cursorOffsetListeners.push_back(listener);
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

    static void removeMousePressedListner(const MousePressed &listner) {
//        mousePressedListeners.erase(std::find(mousePressedListeners.begin(), mousePressedListeners.end(), listner));
    }

    static void removeCursorPositionListener(const CursorPosition &listner) {
//        cursorPositionListeners.erase(std::find(cursorPositionListeners.begin(), cursorPositionListeners.end(), listner));
    }

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void characterCallback(GLFWwindow* window, unsigned int codepoint);
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    static void mouseButtonCallback(GLFWwindow *window, int btn, int action, int mods);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void dropCallback(GLFWwindow* window, int count, const char** paths);
};

#endif // INPUTHANDLER_H