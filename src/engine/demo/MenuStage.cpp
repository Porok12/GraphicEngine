#include "MenuStage.h"

std::shared_ptr<MenuStage> MenuStage::instance = nullptr;

MenuStage::MenuStage() {
    auto rect1 = std::make_shared<Rectangle>(0, 0, 800, 600);
    auto menuStage = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect1)));
    {
        std::shared_ptr<UIComponent> component;

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

        component.reset(new UIButton("Demo5", 550, 150, 100, 50));
        temp5 = component;
        menuStage->add(component);

        component.reset(new UIButton("Demo7", 550, 400, 100, 50));
        temp7 = component;
        menuStage->add(component);
      
        component.reset(new UIButton("Demo6", 550, 250, 100, 50));
        temp6 = component;
        menuStage->add(component);

        std::shared_ptr<UIComponent> label = std::make_shared<UILabel>("Text", 200, 500);
        menuStage->add(label);

        UIComponent* l = label.get();
        component.reset(new UISlider(50, 500, 100, 50));
        std::dynamic_pointer_cast<UISlider>(component)->addChangedCallback([l](float f){
            auto cast = dynamic_cast<UILabel*>(l);
//            std::cout << l << " " << cast << std::endl;
            cast->setText(std::to_string(f));
//            std::dynamic_pointer_cast<UILabel>(l)->setText(std::to_string(f));
        });
        menuStage->add(component);

        component.reset(new UICheckBox(200, 500, 50, 50));
        menuStage->add(component);

        component.reset(new UITextBox(200, 400, 130, 50));
        menuStage->add(component);

        component.reset(new UISelectBox(50, 300, 200, 50));
//        std::dynamic_pointer_cast<UISelectBox>(component)->init();
        std::dynamic_pointer_cast<UISelectBox>(component)->setOptions({"1", "2", "3"});
        std::dynamic_pointer_cast<UISelectBox>(component)->addChangedCallback([](int i){std::cout << i << std::endl;});
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
