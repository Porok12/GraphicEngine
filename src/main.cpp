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

#define SCREEN_WIDTH 800.0f
#define SCREEN_HEIGHT 600.0f

int main(int argc, char *argv[]) {
    Window window(SCREEN_WIDTH, SCREEN_HEIGHT, "Graphic Engine Demo");

    ResourceLoader resourceLoader(boost::filesystem::current_path().parent_path());

    auto modelProgram = std::make_shared<ShaderProgram>("model");
    auto fontProgram = std::make_shared<ShaderProgram>("font");
    auto guiProgram = std::make_shared<ShaderProgram>("gui");
    std::shared_ptr<Font> ubuntu(FontLoader::loadFont("Ubuntu.ttf"));
    FontLoader::destroy();

    Camera camera(fVec3(0, 0, 0));

    Mat4 ortho = Mat4::getOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 100);
    Mat4 projection = Mat4::getProjection(60.0f, SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.f);

    ModelRenderer::getInstance()->setProgram(modelProgram);
    ModelRenderer::getInstance()->setProjection(projection);

    FontRenderer::getInstance()->setProgram(fontProgram)
            .setFont(ubuntu)
            .setProjection(ortho)
            .setPosition(0.9, 0.9)
            .setColor(200, 255, 55)
            .setScale(1.0f);

    PrimitiveRenderer::getInstance()->setProgram(guiProgram);

    auto fun = std::bind(&Camera::processMouseMovement, &camera, // DO NOT USE camera ALONE
            std::placeholders::_1, std::placeholders::_2);
    InputHandler::addCursorOffsetListener(fun);

    InputHandler::addKeyPressedListener([&camera, &window](const int &key){
        if (key == GLFW_KEY_LEFT_CONTROL) {
            camera.toggle();
            window.toggleCursor();
        }
    });

    auto particleProgram = std::make_shared<ShaderProgram>("particle");
    auto texture = ResourceLoader::loadTexture("particle.png");
    ParticleRenderer::getInstance()->setProjection(projection)->setProgram(particleProgram)->setTexture(texture, 8, 8);

    double lastTime, currentTime, deltaTime;

    GUIRenderer::getInstance()->setProgram(guiProgram).setProjection(ortho);

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

        lastTime = currentTime;
        window.update();
    }

    return 0;
}