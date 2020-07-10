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

int main(int argc, char *argv[]) {
    Window window(800, 600, "Demo");

    ResourceLoader resourceLoader(boost::filesystem::current_path().parent_path());

    ShaderProgram shaderProgram("basic");
    ShaderProgram modelProgram("model");
    auto fontProgram = std::make_shared<ShaderProgram>("font");
    auto guiProgram = std::make_shared<ShaderProgram>("gui");
    std::shared_ptr<Font> ubuntu(FontLoader::loadFont("Ubuntu.ttf"));
    FontLoader::destroy();

    Model model;
    model.loadModel(ResourceLoader::getPath("cube.obj", MODEL));

    Mat4 projection = Mat4::getProjection(60.0f, 800.0f/600.0f, 0.1f, 10.f);
    Mat4 ortho = Mat4::getOrtho(-1, 1, -1, 1, -1, 100);
    Mat4 ortho2 = Mat4::getOrtho(0, 800, 0, 600, -1, 100);
    Mat4 view = Mat4::lookAt(fVec3(0, 1, 0), fVec3(0, 1, 1));
    Mat4 mm = Mat4::identity();
    mm = Mat4::scale(0.75f) * mm;
    mm = Mat4::translate(0, 1, 4) * mm;


    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    char buffer[20] = "Demo";
    float a = 0;

    FontRenderer::getInstance()->setProgram(fontProgram)
            .setFont(ubuntu)
            .setProjection(ortho2)
            .setPosition(0.9, 0.9)
            .setColor(200, 255, 55)
            .setScale(1.0f);

    PrimitiveRenderer::getInstance()->setProgram(guiProgram);

    GUIRenderer guiRenderer;
    guiRenderer.setProgram(guiProgram).setProjection(ortho2);



    InputHandler::addKeyPressedListener([&buffer](const int &key){
        if (key == GLFW_KEY_BACKSPACE) {
            char *begin = buffer + strlen((char*)buffer) - 1;
            char *end = begin + 1;
            std::fill(begin, end, 0);
        }
    });

    InputHandler::addCharactersListener([&buffer](const int& code){
        if (code == 347) {
            sprintf(buffer, "%sś", buffer);
        } else {
            sprintf(buffer, "%s%c", buffer, code);
        }
    });

    std::shared_ptr<UIComponent> rootScene;

    bool show = false;
    auto rect1 = std::make_shared<Rectangle>(0, 0, 800, 600);
    auto rect2 = std::make_shared<Rectangle>(50, 50, 350, 250);
    std::shared_ptr<UIFrame> menuStage, composite2;

    menuStage = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect1)));
    {
        std::shared_ptr<UIComponent> component(new UIButton(100, 120, 100, 50));
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([]() { });
        std::dynamic_pointer_cast<UIButton>(component)->addCursorCallback([](UIButton* btn) { });
        menuStage->add(component);

        component.reset(new UIButton("Demo1", 100, 50, 100, 50));
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([&rootScene, &composite2]() { rootScene = composite2; });
        menuStage->add(component);
    }

    composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 220, 100, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([&rootScene, &menuStage]() { rootScene = menuStage; });
        composite2->add(component);
    }

    InputHandler::addMousePressedListner([&rootScene](const double &x, const double &y){rootScene->click(x, 600-y);});
    InputHandler::addCursorPositionListener([&rootScene](const double &x, const double &y){rootScene->cursor(x, 600-y);});

    rootScene = menuStage;


    particlesTest pt;
    pt.init();
    auto v = fVec3(0.0f);

    while (!window.shouldClose()) {
        window.clear(0.3f, 0.3f, 0.3f);

        pt.draw(projection, projection, v);

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

        window.update();
    }

    return 0;
}