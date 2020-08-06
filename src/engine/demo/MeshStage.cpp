#include "MeshStage.h"

std::shared_ptr<MeshStage> MeshStage::instance = nullptr;

MeshStage::MeshStage() {
    auto rect2 = std::make_shared<Rectangle>(10, 10, 200, 500);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 10, 10, 100, 50);
        temp = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint)->setY(new FixedConstraint(500 - 50 - 10 + 5)));
        composite2->add(component);


        std::shared_ptr<UIComponent> label = std::make_shared<UILabel>("0.00", 50, 500);
        label->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(30))
                                          ->setY(new FixedConstraint(22)));
        composite2->add(label);
        UIComponent* label_ptr = label.get();

        component.reset(new UISlider(50, 500, 100, 30, 0, 2, 0.1));
        std::dynamic_pointer_cast<UISlider>(component)->addChangedCallback([this, label_ptr](float f){
            rotationSpeed = f;

            auto cast = dynamic_cast<UILabel*>(label_ptr);
            cast->setText(std::to_string(f).substr(0, 4));
        });
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(90))
                                          ->setY(new FixedConstraint(10)));
        composite2->add(component);

        label.reset(new UILabel("0.00", 50, 500));
        label->setConstraints((new RectangleConstraints())
                                      ->setX(new FixedConstraint(30))
                                      ->setY(new FixedConstraint(45+22)));
        composite2->add(label);
        label_ptr = label.get();

        component.reset(new UISlider(50, 500, 100, 30, 0.001, 2, 0.1));
        std::dynamic_pointer_cast<UISlider>(component)->addChangedCallback([this, label_ptr](float f){
            rotationX = f;

            auto cast = dynamic_cast<UILabel*>(label_ptr);
            cast->setText(std::to_string(f).substr(0, 4));
        });
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(90))
                                          ->setY(new FixedConstraint(50)));
        composite2->add(component);

        label.reset(new UILabel("0.00", 50, 500));
        label->setConstraints((new RectangleConstraints())
                                      ->setX(new FixedConstraint(30))
                                      ->setY(new FixedConstraint(90+22)));
        composite2->add(label);
        label_ptr = label.get();

        component.reset(new UISlider(50, 500, 100, 30, 0.001, 2, 0.1));
        std::dynamic_pointer_cast<UISlider>(component)->addChangedCallback([this, label_ptr](float f){
            rotationY = f;

            auto cast = dynamic_cast<UILabel*>(label_ptr);
            cast->setText(std::to_string(f).substr(0, 4));
        });
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(90))
                                          ->setY(new FixedConstraint(100)));
        composite2->add(component);

        label.reset(new UILabel("0.00", 50, 500));
        label->setConstraints((new RectangleConstraints())
                                      ->setX(new FixedConstraint(30))
                                      ->setY(new FixedConstraint(140+22)));
        composite2->add(label);
        label_ptr = label.get();

        component.reset(new UISlider(50, 500, 100, 30, 0.001, 2, 0.1));
        std::dynamic_pointer_cast<UISlider>(component)->addChangedCallback([this, label_ptr](float f){
            rotationZ = f;

            auto cast = dynamic_cast<UILabel*>(label_ptr);
            cast->setText(std::to_string(f).substr(0, 4));
        });
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(90))
                                          ->setY(new FixedConstraint(150)));
        composite2->add(component);

        component = std::make_shared<UISelectBox>(10, 150, 150, 50);
        std::dynamic_pointer_cast<UISelectBox>(component)->setOptions({"RGB", "Y", "U", "V"});
        std::dynamic_pointer_cast<UISelectBox>(component)->addChangedCallback([this](int i){
            colorTarget = i;
        });
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint())->setY(new FixedConstraint(240)));
        composite2->add(component);

        component = std::make_shared<UICheckBox>(10, 150, 40, 40);
        std::dynamic_pointer_cast<UICheckBox>(component)->addOnChangeCallback([this](bool value){
            if (value) {
                glEnable(GL_MULTISAMPLE);
            } else {
                glDisable(GL_MULTISAMPLE);
            }
        });

        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(10))->setY(new FixedConstraint(190)));
        composite2->add(component);

        label = std::make_shared<UILabel>("Antialiasing", 50, 500);
        label->setConstraints((new RectangleConstraints())
                                      ->setX(new FixedConstraint(120))
                                      ->setY(new FixedConstraint(210)));
        composite2->add(label);
    }

    composite2->update(800, 600);
    rootComponent = composite2;

    model.loadModel(ResourceLoader::getPath("cube.obj", MODEL));
}

void MeshStage::renderUI() {
    UIStage::renderUI();
}

void MeshStage::renderContent(FreeCamera &camera, double dt) {
    Mat4 view = camera.getViewMatrix();
    Mat4 mm = Mat4::identity();
    mm = Mat4::scale(0.75f) * mm;
    mm = Mat4::translate(0, 0, -4) * mm;

    tmp += rotationSpeed * dt * 60;

    ModelRenderer::getInstance()->getProgram()->use().set1i("colorTarget", colorTarget);
    ModelRenderer::getInstance()->setModel( Mat4::rotation(tmp, fVec3(rotationX, rotationY, rotationZ)) * mm);
    ModelRenderer::getInstance()->setView(view);
    ModelRenderer::getInstance()->render(model);
}

const std::shared_ptr<MeshStage> &MeshStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<MeshStage>(new MeshStage);
    }

    return instance;
}