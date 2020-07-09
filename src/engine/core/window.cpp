#include "window.h"

Window::Window(int width, int height, const char* title) {

    if (!glfwInit()) {
        BOOST_LOG_TRIVIAL(error) << "Failed to initialize GLFW";
        throw InitException();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = SmartWindow(glfwCreateWindow(width, height, title, nullptr, nullptr));

    if (!window) {
        BOOST_LOG_TRIVIAL(error) << "Failed to create GLFW window";
        glfwTerminate();
        throw InitException();
    }

    glfwMakeContextCurrent(window.get());

    glewExperimental = GL_TRUE;
    GLenum status = glewInit();
    if (status != GLEW_OK) {
        BOOST_LOG_TRIVIAL(error) << "Failed to initialize GLEW";
        throw InitException();
    }

    glViewport(0, 0, width, height);
//    glEnable(GL_DEPTH_TEST);

    BOOST_LOG_TRIVIAL(debug) << "GLFW Windows was created";


//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//    if (glfwRawMouseMotionSupported())
//        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    glfwSetWindowSizeCallback(window.get(), [](GLFWwindow* window, int w, int h){glViewport(0, 0, w, h);});
    glfwSetMouseButtonCallback(window.get(), InputHandler::mouseButtonCallback);
    glfwSetCursorPosCallback(window.get(), InputHandler::cursorPositionCallback);
    glfwSetKeyCallback(window.get(), InputHandler::keyCallback);
    glfwSetCharCallback(window.get(), InputHandler::characterCallback);
    glfwSetScrollCallback(window.get(), InputHandler::scrollCallback);
    glfwSetDropCallback(window.get(), InputHandler::dropCallback);
}

Window::~Window() {
    glfwTerminate();
}

int Window::shouldClose() {
    return glfwGetKey(window.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window.get());
}

void Window::swapBuffers() {
    glfwSwapBuffers(window.get());
}

void Window::update() {
    glfwSwapBuffers(window.get());
    glfwPollEvents();
}

void Window::clear(float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::getCursor(double &x, double &y) {
    glfwGetCursorPos(window.get(), &x, &y);
}

bool Window::mouseButtonLeft() {
    return glfwGetMouseButton(window.get(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
}
