#include "engine/core/window.h"

std::vector<std::function<void (int, int)>> MainWindow::onResizeListeners;

MainWindow::MainWindow(int width, int height, const char* title)
        : MIN_WIDTH(800), MIN_HEIGHT(600) {

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        throw InitException();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = SmartWindow(glfwCreateWindow(width, height, title, nullptr, nullptr));
    glfwSetWindowSizeLimits(window.get(), MIN_WIDTH, MIN_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);

    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw InitException();
    }

    glfwMakeContextCurrent(window.get());

    glewExperimental = GL_TRUE;
    GLenum status = glewInit();
    if (status != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        throw InitException();
    }

    glViewport(0, 0, width, height);

    std::cout << "GLFW Windows was created" << std::endl;

    glDisable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    glfwSetFramebufferSizeCallback(window.get(), MainWindow::onResize);
    glfwSetWindowSizeCallback(window.get(), [](GLFWwindow* window, int w, int h){glViewport(0, 0, w, h);});
    glfwSetMouseButtonCallback(window.get(), InputHandler::mouseButtonCallback);
    glfwSetCursorPosCallback(window.get(), InputHandler::cursorPositionCallback);
    glfwSetKeyCallback(window.get(), InputHandler::keyCallback);
    glfwSetCharCallback(window.get(), InputHandler::characterCallback);
    glfwSetScrollCallback(window.get(), InputHandler::scrollCallback);
    glfwSetDropCallback(window.get(), InputHandler::dropCallback);

    cursorEnabled = true;
}

MainWindow::~MainWindow() {
    glfwTerminate();
}

int MainWindow::shouldClose() {
    return glfwGetKey(window.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window.get());
}

void MainWindow::swapBuffers() {
    glfwSwapBuffers(window.get());
}

void MainWindow::update() {
    swapBuffers();
    glfwPollEvents();
}

void MainWindow::clear(float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int MainWindow::getKey(int key) {
    return glfwGetKey(window.get(), key);
}

void MainWindow::toggleCursor() {

    if (cursorEnabled) {
        glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    cursorEnabled = !cursorEnabled;
}

void MainWindow::addOnResizeListener(std::function<void (int, int)> listener) {
    this->onResizeListeners.push_back(listener);
}

void MainWindow::onResize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    for(const auto &listener: onResizeListeners) {
        listener(width, height);
    }
}

