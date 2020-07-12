#include "UIStage.h"

UIStage::UIStage() {}
//    : stageManager() {
//
//}

//void UIStage::setManager(const std::shared_ptr<UIStageManager> &manager) {
//    this->stageManager = manager;
//}

UIStage::UIStage(const std::shared_ptr<UIComponent> &rootComponent)
        : rootComponent(rootComponent) {

}

void UIStage::renderUI() {
    if (rootComponent) {
        GUIRenderer::getInstance()->render(rootComponent.get());
    }
}

void UIStage::click(const double &x, const double &y) {
    rootComponent->click(x, y);
}

void UIStage::cursor(const double &x, const double &y) {
    rootComponent->cursor(x, y);
}

std::shared_ptr<MenuStage> MenuStage::instance = nullptr;

MenuStage::MenuStage() {
    auto rect1 = std::make_shared<Rectangle>(0, 0, 800, 600);
    auto menuStage = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect1)));
    {
        std::shared_ptr<UIComponent> component(new UIButton(100, 120, 100, 50));
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([]() { std::cout << "@\n"; });
//        std::dynamic_pointer_cast<UIButton>(component)->addCursorCallback([](UIButton* btn) {
//            if (auto manager = stageManager.lock()) {
//                manager->setStage(Stages::PARTICLES);
//            }
//        });

        menuStage->add(component);

        component.reset(new UIButton("Demo1", 100, 50, 100, 50));
        temp = component;
//        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([&stageManager]() {  });
        menuStage->add(component);
    }

    rootComponent = menuStage;
}

void MenuStage::renderUI() {
    UIStage::renderUI();
}

void MenuStage::renderContent(Camera camera, double dt) { }

std::shared_ptr<UIStage> MenuStage::getInstance() {
    if (!instance) {
        instance = std::make_shared<MenuStage>();
    }

    return instance;
}

//MenuStage* MenuStage::getInstance() {
//    if (!instance) {
//        instance = std::make_shared<MenuStage>();
//    }
//
//    return instance.get();
//}

std::shared_ptr<MeshStage> MeshStage::instance = nullptr;

MeshStage::MeshStage()
        : pg(2.0f) {
//    auto particleProgram = std::make_shared<ShaderProgram>("particle");
//    auto texture = ResourceLoader::loadTexture("particle.png");
//    ParticleRenderer::getInstance()->setProjection(projection)->setProgram(particleProgram)->setTexture(texture, 8, 8);

    auto rect2 = std::make_shared<Rectangle>(50, 50, 350, 250);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 220, 100, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback(fun);
//        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([&stageManager]() {
//            if (auto manager = stageManager.lock()) {
//                manager->setStage(Stages::PARTICLES);
//            }
//        });
        composite2->add(component);
    }

    rootComponent = composite2;
}

void MeshStage::renderUI() {
    UIStage::renderUI();
}

void MeshStage::renderContent(Camera camera, double dt) {
    pg.update(dt);

    Mat4 view = camera.getViewMatrix();
    ParticleRenderer::getInstance()
            ->setRight(camera.getRight())
            ->setUp(camera.getUp())
            ->setCamera(camera.getPos())
            ->setView(view)
            ->render(pg.getParticles(), pg.getLifeTime());
}

std::shared_ptr<UIStage> MeshStage::getInstance() {
    if (!instance) {
        instance = std::make_shared<MeshStage>();
    }

    return instance;
}