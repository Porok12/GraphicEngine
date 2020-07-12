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
#include <gui/Primitives/PrimitiveRenderer.h>
#include <gui/UIRenderer.h>
#include <gui/UIComponent.h>
#include <gui/UIComposite.h>
#include <gui/UIButton.h>
#include <gui/UIFrame.h>
#include <gui/UIFrameDecorator.h>
#include <gui/UIStage.h>
#include <core/particles/Particle.h>
#include <core/particles/ParticleGenerator.h>
#include <core/particles/ParticleRenderer.h>
#include <core/Camera.h>
#include <gui/UIStageManager.h>

int main(int argc, char *argv[]) {
    Window window(800, 600, "Demo");

    ResourceLoader resourceLoader(boost::filesystem::current_path().parent_path());

    ShaderProgram shaderProgram("basic");
    ShaderProgram modelProgram("model");
    auto fontProgram = std::make_shared<ShaderProgram>("font");
    auto guiProgram = std::make_shared<ShaderProgram>("gui");
    std::shared_ptr<Font> ubuntu(FontLoader::loadFont("Ubuntu.ttf"));
    FontLoader::destroy();

    Camera camera(fVec3(0, 0, 0));

    Model model;
    model.loadModel(ResourceLoader::getPath("cube.obj", MODEL));



    Mat4 projection = Mat4::getProjection(60.0f, 800.0f/600.0f, 0.1f, 100.f);
    Mat4 ortho2 = Mat4::getOrtho(0, 800, 0, 600, -1, 100);
    Mat4 view = camera.getViewMatrix();
    Mat4 mm = Mat4::identity();
    mm = Mat4::scale(0.75f) * mm;
    mm = Mat4::translate(0, 1, 4) * mm;



//    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    char buffer[20] = "Demo";
    float a = 0;

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

    InputHandler::addCharactersListener([&buffer](const int& code){
        sprintf(buffer, "%s%c", buffer, code);
    });

//    std::shared_ptr<UIComponent> rootScene;
//
//    bool show = false;
//    auto rect1 = std::make_shared<Rectangle>(0, 0, 800, 600);
//    auto rect2 = std::make_shared<Rectangle>(50, 50, 350, 250);
//    std::shared_ptr<UIFrame> menuStage, composite2;
//
//    menuStage = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect1)));
//    {
//        std::shared_ptr<UIComponent> component(new UIButton(100, 120, 100, 50));
//        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([]() { });
//        std::dynamic_pointer_cast<UIButton>(component)->addCursorCallback([](UIButton* btn) { });
//        menuStage->add(component);
//
//        component.reset(new UIButton("Demo1", 100, 50, 100, 50));
//        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([&rootScene, &composite2]() { rootScene = composite2; });
//        menuStage->add(component);
//    }
//
//    composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
//    {
//        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 220, 100, 100, 50);
//        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([&rootScene, &menuStage]() { rootScene = menuStage; });
//        composite2->add(component);
//    }
//
//    InputHandler::addMousePressedListner([&rootScene](const double &x, const double &y){rootScene->click(x, 600-y);});
//    InputHandler::addCursorPositionListener([&rootScene](const double &x, const double &y){rootScene->cursor(x, 600-y);});
//
//    rootScene = menuStage;

    auto particleProgram = std::make_shared<ShaderProgram>("particle");
    auto texture = ResourceLoader::loadTexture("particle.png");
    ParticleRenderer::getInstance()->setProjection(projection)->setProgram(particleProgram)->setTexture(texture, 8, 8);

    ParticleGenerator pg(2.0f);

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

//        pg.update(deltaTime);
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

//        view = camera.getViewMatrix();
//        ParticleRenderer::getInstance()
//                ->setRight(camera.getRight())
//                ->setUp(camera.getUp())
//                ->setCamera(camera.getPos())
//                ->setView(view)
//                ->render(pg.getParticles(), pg.getLifeTime());


        stageManager.render();

//        modelProgram.use()
//                .setMatrix4("projection", projection)
//                .setMatrix4("view", view)
//                .setMatrix4("model", Mat4::rotation(a++, fVec3(0.9, 0.6, 0.3)) * mm);
//        model.draw(modelProgram);
//
//        FontRenderer::getInstance()->setScale(1.0f).setPosition(400, 300).render(buffer);
//
//        guiProgram->use().setMatrix4("ortho", ortho2);
//        guiRenderer.render(rootScene.get());

        lastTime = currentTime;
        window.update();
    }

    return 0;
}