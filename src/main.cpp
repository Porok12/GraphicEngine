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
#include <memory>
#include <core/text/Font.h>
#include <core/text/FontRenderer.h>
#include <gui/UIStageManager.h>
#include <core/particles/ParticleRenderer.h>
#include <core/models/ModelRenderer.h>

int main(int argc, char *argv[]) {
    Window window(800, 600, "Demo");

    ResourceLoader resourceLoader(boost::filesystem::current_path().parent_path());

    ShaderProgram shaderProgram("basic");
    auto modelProgram = std::make_shared<ShaderProgram>("model");
    auto fontProgram = std::make_shared<ShaderProgram>("font");
    auto guiProgram = std::make_shared<ShaderProgram>("gui");
    std::shared_ptr<Font> ubuntu(FontLoader::loadFont("Ubuntu.ttf"));
    FontLoader::destroy();

    Camera camera(fVec3(0, 0, 0));

    Mat4 ortho2 = Mat4::getOrtho(0, 800, 0, 600, -1, 100);
    Mat4 projection = Mat4::getProjection(60.0f, 800.0f/600.0f, 0.1f, 100.f);
//    Mat4 view = camera.getViewMatrix();
//    Mat4 mm = Mat4::identity();
//    mm = Mat4::scale(0.75f) * mm;
//    mm = Mat4::translate(0, 1, 4) * mm;

    ModelRenderer::getInstance()->setProgram(modelProgram);
    ModelRenderer::getInstance()->setProjection(projection);


//    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    char buffer[20] = "Demo";

    FontRenderer::getInstance()->setProgram(fontProgram)
            .setFont(ubuntu)
            .setProjection(ortho2)
            .setPosition(0.9, 0.9)
            .setColor(200, 255, 55)
            .setScale(1.0f);

    PrimitiveRenderer::getInstance()->setProgram(guiProgram);

    auto fun = std::bind(&Camera::processMouseMovement, &camera, // DO NOT USE camera ALONE
            std::placeholders::_1, std::placeholders::_2);
    InputHandler::addCursorOffsetListener(fun);

    InputHandler::addKeyPressedListener([&buffer](const int &key){
        if (key == GLFW_KEY_BACKSPACE) {
            char *begin = buffer + strlen((char*)buffer) - 1;
            char *end = begin + 1;
            std::fill(begin, end, 0);
        }
    });

    InputHandler::addKeyPressedListener([&camera, &window](const int &key){
        if (key == GLFW_KEY_LEFT_CONTROL) {
            camera.toggle();
            window.toggleCursor();
        }
    });

    InputHandler::addCharactersListener([&buffer](const int& code){
        sprintf(buffer, "%s%c", buffer, code);
    });

    auto particleProgram = std::make_shared<ShaderProgram>("particle");
    auto texture = ResourceLoader::loadTexture("particle.png");
    ParticleRenderer::getInstance()->setProjection(projection)->setProgram(particleProgram)->setTexture(texture, 8, 8);

    double lastTime, currentTime, deltaTime;

//    glEnable(GL_DEPTH_TEST);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    GUIRenderer::getInstance()->setProgram(guiProgram).setProjection(ortho2);

    UIStageManager stageManager;
    stageManager.setStage(Stages::MENU);

    InputHandler::addMousePressedListner([&stageManager](const double &x, const double &y){stageManager.click(x, 600-y);});
    InputHandler::addCursorPositionListener([&stageManager](const double &x, const double &y){stageManager.cursor(x, 600-y);});

    while (!window.shouldClose()) {
        window.clear(0.3f, 0.3f, 0.3f);
        currentTime = glfwGetTime();

        stageManager.update(camera, deltaTime);
        deltaTime = currentTime - lastTime;

        if (window.getKey(GLFW_KEY_D))
            camera.processKeyboard(Camera_Movement::RIGHT, deltaTime);
        if (window.getKey(GLFW_KEY_A))
            camera.processKeyboard(Camera_Movement::LEFT, deltaTime);
        if (window.getKey(GLFW_KEY_W))
            camera.processKeyboard(Camera_Movement::FORWARD, deltaTime);
        if (window.getKey(GLFW_KEY_S))
            camera.processKeyboard(Camera_Movement::BACKWARD, deltaTime);

        stageManager.render();

//        FontRenderer::getInstance()->setScale(1.0f).setPosition(400, 300).render(buffer);

        lastTime = currentTime;
        window.update();
    }

    return 0;
}