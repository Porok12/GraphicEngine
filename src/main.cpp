#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>
#include <core/window.h>
#include <core/shaders/ShaderLoader.h>
#include <core/shaders/ShaderProgram.h>
#include <core/utils/ResourceLoader.h>
#include <core/models/Model.h>

#include <math/Mat4.h>
#include <core/text/FontLoader.h>
#include <iostream>
#include <core/text/Font.h>
#include <core/text/FontRenderer.h>

int main(int argc, char *argv[]) {
    Window window(800, 600, "Demo");

    ResourceLoader resourceLoader(boost::filesystem::current_path().parent_path());

    ShaderProgram shaderProgram("basic");
    ShaderProgram modelProgram("model");
    auto fontProgram = std::make_shared<ShaderProgram>("font");
    std::shared_ptr<Font> ubuntu(FontLoader::loadFont("Ubuntu.ttf"));
    FontLoader::destroy();

    Model model;
    model.loadModel(ResourceLoader::getPath("cube.obj", MODEL));

    Mat4 projection = Mat4::getProjection(60.0f, 800.0f/600.0f, 0.1f, 10.f);
    Mat4 ortho = Mat4::getOrtho(-1, 1, -1, 1, -1, 100);
//    Mat4 view = Mat4::lookAt(fVec3(0, 0, 0), fVec3(0, 0.5, -1));
//    Mat4 mm = Mat4::translate(0, 0, -5);
    Mat4 view = Mat4::lookAt(fVec3(0, 1, 0), fVec3(0, 1, 1));
    Mat4 mm = Mat4::identity();
    mm = Mat4::scale(0.75f) * mm;
    mm = Mat4::translate(0, 1, 4) * mm;
//    mm = Mat4::rotationX(100.0f) * mm;
//    mm = Mat4::scale(mm, 0.75f);


    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

//    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    char buffer[20];

    float a = 0;
    FontRenderer fontRenderer;
    fontRenderer.setProgram(fontProgram)
            .setFont(ubuntu)
            .setProjection(ortho)
            .setPosition(0.9, 0.9)
            .setColor(200, 255, 55)
            .setScale(1.0f);

    while (!window.shouldClose()) {
        window.clear(0.3f, 0.3f, 0.3f);

        modelProgram.use()
                .setMatrix4("projection", projection)
                .setMatrix4("view", view)
                .setMatrix4("model", Mat4::rotation(a++, fVec3(0.9, 0.6, 0.3)) * mm);
        model.draw(modelProgram);

        sprintf(buffer, "Demo %.2f", glfwGetTime());
        fontRenderer.render(buffer);

        window.update();
    }

    return 0;
}