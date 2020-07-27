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

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char *argv[]) {
    MainWindow window(SCREEN_WIDTH, SCREEN_HEIGHT, "Graphic Engine Demo");

    ResourceLoader resourceLoader(boost::filesystem::path().relative_path());

    auto modelProgram = std::make_shared<ShaderProgram>("model");
    auto fontProgram = std::make_shared<ShaderProgram>("font");
    auto guiProgram = std::make_shared<ShaderProgram>("gui");
    std::shared_ptr<Font> ubuntu(FontLoader::loadFont("Ubuntu.ttf"));
    FontLoader::destroy();

    auto camera = std::make_shared<Camera>(fVec3(0, 0, 0));

    Mat4 ortho = Mat4::getOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 100);
    Mat4 projection = Mat4::getProjection(60.0f, SCREEN_WIDTH / static_cast<float>(SCREEN_HEIGHT), 0.1f, 100.f);
    window.addOnResizeListener([&projection, &ortho](int w, int h){
        projection = Mat4::getProjection(60.0f, w / static_cast<float>(h), 0.1f, 100.f);
        ModelRenderer::getInstance()->setProjection(projection);
        ParticleRenderer::getInstance()->setProjection(projection);

        ortho = Mat4::getOrtho(0, w, 0, h, -1, 100);
        FontRenderer::getInstance()->setProjection(ortho);
        GUIRenderer::getInstance()->setProjection(ortho);
        GUIRenderer::getInstance()->update(w, h);
    });

    ModelRenderer::getInstance()->setProgram(modelProgram);
    ModelRenderer::getInstance()->setProjection(projection);

    FontRenderer::getInstance()->setProgram(fontProgram)
            .setFont(ubuntu)
            .setProjection(ortho)
            .setPosition(0.9, 0.9)
            .setColor(200, 255, 55)
            .setScale(1.0f);

    PrimitiveRenderer::getInstance()->setProgram(guiProgram);

    auto fun = std::bind(&Camera::processMouseMovement, &*camera.get(),
            std::placeholders::_1, std::placeholders::_2);
    InputHandler::addCursorOffsetListener(fun);

    InputHandler::addKeyPressedListener([&camera, &window](const int &key){
        if (key == GLFW_KEY_LEFT_CONTROL) {
            camera->toggle();
            window.toggleCursor();
        }
    });

    auto particleProgram = std::make_shared<ShaderProgram>("particle");
    auto texture = ResourceLoader::loadTexture("particle.png");
    ParticleRenderer::getInstance()->setProjection(projection)->setProgram(particleProgram)->setTexture(texture, 8, 8);

    double lastTime, currentTime, deltaTime;

    GUIRenderer::getInstance()->setProgram(guiProgram).setProjection(ortho);

    UIStageManager stageManager(camera);
    stageManager.setStage(Stages::MENU);
    auto clickLambda = [&stageManager](const double &x, const double &y){stageManager.click(x, y);};
    auto cursorLambda = [&stageManager](const double &x, const double &y){stageManager.cursor(x, y);};
    InputHandler::addMousePressedListner(clickLambda);
    InputHandler::addCursorPositionListener(cursorLambda);
    InputHandler::addKeyPressedListener([&stageManager](const int &key){
        if (key == GLFW_KEY_LEFT_CONTROL) {
            stageManager.setDisabled(!stageManager.isDisabled());
        }
    });


    while (!window.shouldClose()) {
        window.clear(0.3f, 0.3f, 0.3f);
        currentTime = glfwGetTime();

        stageManager.update(deltaTime);
        deltaTime = currentTime - lastTime;

        if (window.getKey(GLFW_KEY_D))
            camera->processKeyboard(Camera_Movement::RIGHT, deltaTime);
        if (window.getKey(GLFW_KEY_A))
            camera->processKeyboard(Camera_Movement::LEFT, deltaTime);
        if (window.getKey(GLFW_KEY_W))
            camera->processKeyboard(Camera_Movement::FORWARD, deltaTime);
        if (window.getKey(GLFW_KEY_S))
            camera->processKeyboard(Camera_Movement::BACKWARD, deltaTime);

        stageManager.render();

        lastTime = currentTime;
        window.update();
    }

    return EXIT_SUCCESS;
}