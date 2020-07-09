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

void foo() {
    std::cerr << "foo" << std::endl;
}

class XXX {
public:
    void foo() {
        std::cerr << "foo" << std::endl;
    }
};

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

    char buffer[20] = "Demo";

    float a = 0;
//    FontRenderer fontRenderer;
    FontRenderer::getInstance()->setProgram(fontProgram)
            .setFont(ubuntu)
            .setProjection(ortho2)
            .setPosition(0.9, 0.9)
            .setColor(200, 255, 55)
            .setScale(1.0f);

    PrimitiveRenderer::getInstance()->setProgram(guiProgram);

    GUIRenderer guiRenderer;
    guiRenderer.setProgram(guiProgram).setProjection(ortho2);

//    XXX xxx;
//    btn->f1 = std::bind(&XXX::foo, xxx);
//    btn->f1 = [](){ std::cerr << "lambda" << std::endl; };
//    btn->f1 = &foo;

//    InputHandler::addMousePressedListner([](){std::cout << "Pressed" << std::endl;});
//    InputHandler::addCursorPositionListener([](const double &x, const double &y){std::cout << "Cursor " << x << " " << y << std::endl;});
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


    auto rect1 = std::make_shared<Rectangle>(50, 50, 400, 250);
    std::shared_ptr<UIFrame> composite(new UIFrameDecorator(new UIFrame(rect1)));
    {
        std::shared_ptr<UIComponent> component(new UIButton(100, 100, 100, 100));
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([]() { std::cout << "@\n"; });
        std::dynamic_pointer_cast<UIButton>(component)->addCursorCallback([](UIButton* btn) { });
        composite->add(component);

        component.reset(new UIButton(50, 50, 80, 80));
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([]() { std::cout << "#\n"; });
        composite->add(component);
    }

    InputHandler::addMousePressedListner([&composite](const double &x, const double &y){composite->click(x, 600-y);});
    InputHandler::addCursorPositionListener([&composite](const double &x, const double &y){composite->cursor(x, 600-y);});

    while (!window.shouldClose()) {
        window.clear(0.3f, 0.3f, 0.3f);

        modelProgram.use()
                .setMatrix4("projection", projection)
                .setMatrix4("view", view)
                .setMatrix4("model", Mat4::rotation(a++, fVec3(0.9, 0.6, 0.3)) * mm);
        model.draw(modelProgram);

        FontRenderer::getInstance()->setScale(1.0f).setPosition(400, 300).render(buffer);

        guiProgram->use().setMatrix4("ortho", ortho2);
        guiRenderer.render(composite.get());

        window.update();
    }

    return 0;
}