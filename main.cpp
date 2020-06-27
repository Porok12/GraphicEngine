#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <SOIL.h>

int main(int argc, char *argv[]) {
    FT_Library ft;
    Assimp::Importer importer;

    GLuint tex_2d = SOIL_load_OGL_texture("img.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

    if(0 == tex_2d) {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }

    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "GraphicEngine Demo", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}