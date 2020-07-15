#include "MenuStage.h"

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

        component.reset(new UIButton("Demo2", 250, 50, 100, 50));
        temp2 = component;
        menuStage->add(component);

        component.reset(new UIButton("Demo3", 400, 50, 100, 50));
        temp3 = component;
        menuStage->add(component);

        component.reset(new UIButton("Demo4", 550, 50, 100, 50));
        temp4 = component;
        menuStage->add(component);
    }

    rootComponent = menuStage;
}

void MenuStage::renderUI() {
    UIStage::renderUI();
}

void MenuStage::renderContent(Camera camera, double dt) { }

const std::shared_ptr<MenuStage> & MenuStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<MenuStage>(new MenuStage);
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