#include "InputHandler.h"

std::vector<MousePressed> InputHandler::mousePressedListeners;
std::vector<CursorPosition> InputHandler::cursorPositionListeners;
std::vector<KeyPressed> InputHandler::keyPressedListeners;
std::vector<ScrollOffset> InputHandler::scrollOffsetListeners;
std::vector<CharacterCode> InputHandler::charactersListeners;
bool InputHandler::leftButton = false;
bool InputHandler::keys[128];

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
    for (const auto &listener: cursorPositionListeners) {
        listener(xpos, ypos);
    }
}

void InputHandler::mouseButtonCallback(GLFWwindow *window, int btn, int action, int mods) {
    if (action == GLFW_RELEASE && leftButton) {
        for(const auto &listener: mousePressedListeners) {
            listener();
        }
    }

    leftButton = action != GLFW_RELEASE;
}

void InputHandler::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    for(const auto &listener: scrollOffsetListeners) {
        listener(xoffset, yoffset);
    }
}

void InputHandler::dropCallback(GLFWwindow* window, int count, const char **paths) {
    for (int i = 0; i < count; ++i) {
        std::cout << paths[i] << std::endl;
    }
}
