#include "definitions.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum class MouseButtons {
    LEFT_BUTTON = GLFW_MOUSE_BUTTON_LEFT,
    MIDDLE_BUTTON = GLFW_MOUSE_BUTTON_MIDDLE,
    RIGHT_BUTTON = GLFW_MOUSE_BUTTON_RIGHT
};

enum class MouseActions {
    PRESSED = GLFW_PRESS,
    RELEASED = GLFW_RELEASE,
    REPEAT = GLFW_REPEAT
};