#include "window.h"

Window::Window(int width, int height, const char* title) {

    if (!glfwInit()) {
        BOOST_LOG_TRIVIAL(error) << "Failed to initialize GLFW";
        throw InitException();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window) {
        BOOST_LOG_TRIVIAL(error) << "Failed to create GLFW window";
        glfwTerminate();
        throw InitException();
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum status = glewInit();
    if (status != GLEW_OK) {
        BOOST_LOG_TRIVIAL(error) << "Failed to initialize GLEW";
        throw InitException();
    }

    glViewport(0, 0, width, height);
//    glEnable(GL_DEPTH_TEST);

    BOOST_LOG_TRIVIAL(debug) << "GLFW Windows was created";

    glfwSetKeyCallback(window, keyCallback);
}

Window::~Window() {
    glfwTerminate();
}

int Window::shouldClose() {
    return glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

void Window::update() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::clear(float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        std::cout << key << std::endl;
}
