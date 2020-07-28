#include "MenuStage.h"

std::shared_ptr<MenuStage> MenuStage::instance = nullptr;

MenuStage::MenuStage() {
    auto rect1 = std::make_shared<Rectangle>(0, 0, 800, 600);
    auto menuStage = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect1)));
    {
        std::shared_ptr<UIComponent> component;

        component.reset(new UIButton("Model/YUV demo", 375, 50, 250, 50));
        temp = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint())
                                          ->setY(new FixedConstraint(50)));
        menuStage->add(component);

        component.reset(new UIButton("Particles demo", 375, 110, 250, 50));
        temp2 = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint())
                                          ->setY(new FixedConstraint(110)));
        menuStage->add(component);

        component.reset(new UIButton("Shading demo", 375, 170, 250, 50));
        temp3 = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint())
                                          ->setY(new FixedConstraint(170)));
        menuStage->add(component);

        component.reset(new UIButton("Light demo", 375, 230, 250, 50));
        temp4 = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint())
                                          ->setY(new FixedConstraint(230)));
        menuStage->add(component);

        component.reset(new UIButton("Textures demo", 375, 290, 250, 50));
        temp5 = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint())
                                          ->setY(new FixedConstraint(290)));
        menuStage->add(component);

        component.reset(new UIButton("Blur demo", 375, 410, 250, 50));
        temp7 = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint())
                                          ->setY(new FixedConstraint(410)));
        menuStage->add(component);
      
        component.reset(new UIButton("Dithering demo", 375, 350, 250, 50));
        temp6 = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint())
                                          ->setY(new FixedConstraint(350)));
        menuStage->add(component);

        component.reset(new UITextBox(50, 400, 130, 50));
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(10))
                                          ->setY(new FixedConstraint(10)));
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

void MenuStage::renderContent(FreeCamera camera, double dt) { }

const std::shared_ptr<MenuStage> & MenuStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<MenuStage>(new MenuStage);
    }

    return instance;
}
