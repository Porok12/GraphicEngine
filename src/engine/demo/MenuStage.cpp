#include "MenuStage.h"

std::shared_ptr<MenuStage> MenuStage::instance = nullptr;

MenuStage::MenuStage() {
    auto rect1 = std::make_shared<Rectangle>(0, 0, 800, 600);
    auto menuStage = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect1)));
    {
        std::shared_ptr<UIComponent> component;

        component.reset(new UIButton("Demo1", 375, 50, 100, 50));
        temp = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint())
                                          ->setY(new FixedConstraint(50)));
        menuStage->add(component);

        component.reset(new UIButton("Demo2", 375, 110, 100, 50));
        temp2 = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint())
                                          ->setY(new FixedConstraint(110)));
        menuStage->add(component);

        component.reset(new UIButton("Demo3", 375, 170, 100, 50));
        temp3 = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint())
                                          ->setY(new FixedConstraint(170)));
        menuStage->add(component);

        component.reset(new UIButton("Demo4", 375, 230, 100, 50));
        temp4 = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint())
                                          ->setY(new FixedConstraint(230)));
        menuStage->add(component);

        component.reset(new UIButton("Demo5", 375, 290, 100, 50));
        temp5 = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint())
                                          ->setY(new FixedConstraint(290)));
        menuStage->add(component);

        component.reset(new UIButton("Demo7", 375, 410, 100, 50));
        temp7 = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint())
                                          ->setY(new FixedConstraint(410)));
        menuStage->add(component);
      
        component.reset(new UIButton("Demo6", 375, 350, 100, 50));
        temp6 = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint())
                                          ->setY(new FixedConstraint(350)));
        menuStage->add(component);

        std::shared_ptr<UIComponent> label = std::make_shared<UILabel>("Text", 50, 500);
        label->setConstraints((new RectangleConstraints())
                                      ->setX(new FixedConstraint(50))
                                      ->setY(new FixedConstraint(500)));
        menuStage->add(label);

        UIComponent* l = label.get();
        component.reset(new UISlider(50, 500, 100, 50));
        std::dynamic_pointer_cast<UISlider>(component)->addChangedCallback([l](float f){
            auto cast = dynamic_cast<UILabel*>(l);
            cast->setText(std::to_string(f));
        });
        component->setConstraints((new RectangleConstraints())
                                      ->setX(new FixedConstraint(50))
                                      ->setY(new FixedConstraint(400)));
        menuStage->add(component);

        component.reset(new UICheckBox(50, 500, 50, 50));
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(50))
                                          ->setY(new FixedConstraint(300)));
        menuStage->add(component);

        component.reset(new UITextBox(50, 400, 130, 50));
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(50))
                                          ->setY(new FixedConstraint(200)));
        menuStage->add(component);

        component.reset(new UISelectBox(50, 300, 200, 50));
        std::dynamic_pointer_cast<UISelectBox>(component)->setOptions({"1", "2", "3"});
        std::dynamic_pointer_cast<UISelectBox>(component)->addChangedCallback([](int i){std::cout << i << std::endl;});
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(50))
                                          ->setY(new FixedConstraint(100)));
        menuStage->add(component);
    }

    menuStage->setConstraints((new RectangleConstraints())
                                      ->setX(new FixedConstraint(0))
                                      ->setY(new FixedConstraint(0))
                                      ->setW(new RelativeConstraint(1))
                                      ->setH(new RelativeConstraint(1)));
    menuStage->update(800, 600);
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
