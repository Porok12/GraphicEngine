#include "engine/core/InputHandler.h"

std::vector<MouseAction> InputHandler::mouseActionListeners;
std::vector<MouseButton> InputHandler::mouseButtonListeners;
std::vector<MousePressed> InputHandler::mousePressedListeners;
std::vector<MouseRelease> InputHandler::mouseReleaseListeners;
std::vector<CursorPosition> InputHandler::cursorPositionListeners;
std::vector<CursorOffset> InputHandler::cursorOffsetListeners;
std::vector<KeyPressed> InputHandler::keyPressedListeners;
std::vector<ScrollOffset> InputHandler::scrollOffsetListeners;
std::vector<CharacterCode> InputHandler::charactersListeners;
std::vector<PathDrop> InputHandler::dropListeners;
bool InputHandler::buttons[8];
bool InputHandler::keys[512];
double InputHandler::x, InputHandler::y;
bool InputHandler::updated = false;

void InputHandler::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_RELEASE && keys[key]) {
        for (const auto &listener: keyPressedListeners) {
            listener(key);
        }
    }

    keys[key] = action != GLFW_RELEASE;
}

void InputHandler::characterCallback(GLFWwindow* window, unsigned int codepoint) {
    for(const auto &listener: charactersListeners) {
        listener(codepoint);
    }
}

void InputHandler::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ypos = height - ypos;

    for (const auto &listener: cursorPositionListeners) {
        listener(xpos, ypos);
    }

    if (InputHandler::updated) {
        for (const auto &listener: cursorOffsetListeners) {
            listener(xpos-x, y-ypos);
        }
    }

    InputHandler::x = xpos;
    InputHandler::y = ypos;
    InputHandler::updated = true;
}

void InputHandler::mouseButtonCallback(GLFWwindow *window, int btn, int action, int mods) {
    if (action == GLFW_RELEASE && buttons[btn]) {
        for(const auto &listener: mousePressedListeners) {
            listener(InputHandler::x, InputHandler::y);
        }
    }

    if (action == GLFW_PRESS && !buttons[btn]) {
        for(const auto &listener: mouseButtonListeners) {
            listener(InputHandler::x, InputHandler::y);
        }
    }

    if (action == GLFW_RELEASE && buttons[btn]) {
        for(const auto &listener: mouseReleaseListeners) {
            listener(InputHandler::x, InputHandler::y);
        }
    }

    for(const auto &listener: mouseActionListeners) {
        listener(InputHandler::x, InputHandler::y, btn, action);
    }

    buttons[btn] = action != GLFW_RELEASE;
}

void InputHandler::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    for(const auto &listener: scrollOffsetListeners) {
        listener(xoffset, yoffset);
    }
}

void InputHandler::dropCallback(GLFWwindow* window, int count, const char **paths) {
    for (int i = 0; i < count; ++i) {
        std::cout << "Dropped path: " << paths[i] << std::endl;
        for (const auto &listener: dropListeners) {
            listener(paths[i]);
        }
    }
}
