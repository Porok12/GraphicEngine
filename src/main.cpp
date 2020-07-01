#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>
#include <core/window.h>
#include <core/shaders/ShaderLoader.h>
#include <core/shaders/ShaderProgram.h>
#include <core/utils/ResourceLoader.h>

int main(int argc, char *argv[]) {
    Window window(800, 600, "Demo");

    ResourceLoader resourceLoader(boost::filesystem::current_path().parent_path());

    ShaderProgram shaderProgram("basic");

    float vertices[] = {
            0.9f, 0.9f, 0.0f,
            0.9f, -0.9f, 0.0f,
            -0.9f, -0.9f, 0.0f,
            -0.9f, 0.9f, 0.0f
    };

    unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!window.shouldClose()) {
        window.clear(0.3f, 0.3f, 0.3f);

        shaderProgram.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        window.update();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    return 0;
}