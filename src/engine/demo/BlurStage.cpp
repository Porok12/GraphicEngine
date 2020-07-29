#include "BlurStage.h"

std::shared_ptr<BlurStage> BlurStage::instance = nullptr;

BlurStage::BlurStage() : bloom() {

    auto rect2 = std::make_shared<Rectangle>(10, 10, 200, 500);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 10, 10, 100, 50);
        temp = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint)
                                          ->setY(new FixedConstraint(500 - 50 - 10)));
        composite2->add(component);

        component = std::make_shared<UISelectBox>(10, 70, 150, 50);
        std::dynamic_pointer_cast<UISelectBox>(component)->setOptions({"Kernel 1x1", "Kernel 3x3", "Kernel 5x5", "Kernel 9x9", "Kernel 15x15"});
        std::dynamic_pointer_cast<UISelectBox>(component)->addChangedCallback([this](int i){
            switch (i) {
                case 0: bloom.setKernelSize(1);
                    break;
                case 1: bloom.setKernelSize(3);
                    break;
                case 2: bloom.setKernelSize(5);
                    break;
                case 3: bloom.setKernelSize(9);
                    break;
                case 4: bloom.setKernelSize(15);
                    break;
            }
        });
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint)
                                          ->setY(new FixedConstraint(10)));
        composite2->add(component);

        std::shared_ptr<UIComponent> label = std::make_shared<UILabel>("0.1", 50, 500);
        label->setConstraints((new RectangleConstraints())
                                      ->setX(new FixedConstraint(150))
                                      ->setY(new FixedConstraint(250+104)));
        composite2->add(label);

        component = std::make_shared<UISlider>(10, 90, 100, 30, 0.1, 2, 0.1);
        std::dynamic_pointer_cast<UISlider>(component)->addChangedCallback([this, label](double f) {
            bloom.setSigma(f);

            auto cast = dynamic_cast<UILabel*>(label.get());
            cast->setText(std::to_string(f).substr(0, 3));
        });
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(10))
                                          ->setY(new FixedConstraint(250+90)));
        composite2->add(component);

        label = std::make_shared<UILabel>("0", 50, 500);
        label->setConstraints((new RectangleConstraints())
                                      ->setX(new FixedConstraint(150))
                                      ->setY(new FixedConstraint(250+144)));
        composite2->add(label);

        component = std::make_shared<UISlider>(10, 90, 100, 30, 0, 9, 1);
        std::dynamic_pointer_cast<UISlider>(component)->addChangedCallback([this, label](double f) {
            bloom.setIterations(f);

            auto cast = dynamic_cast<UILabel*>(label.get());
            cast->setText(std::to_string(f).substr(0, 1));
        });
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(10))
                                          ->setY(new FixedConstraint(250+130)));
        composite2->add(component);
    }

    composite2->update(800, 600);
    rootComponent = composite2;

    plane.enableBumpMapping(false);
    plane.loadModel(ResourceLoader::getPath("plane.obj", MODEL));

    program = std::make_shared<ShaderProgram>("final_gaussian");
    textureID = ResourceLoader::loadTexture("grid.png");
}

void BlurStage::renderUI() {
    UIStage::renderUI();
}

void BlurStage::renderContent(FreeCamera camera, double dt) {
    GLuint tex = bloom.apply(textureID);

    program->use();
    program->set3f("viewPos", camera.getPos());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);

    Mat4 view = camera.getViewMatrix();
    ModelRenderer::getInstance()->setView(view);
    Mat4 mm = Mat4::identity();
    mm = Mat4::rotationX(-90.f) * Mat4::translate(0, 0, -8) * mm;
    ModelRenderer::getInstance()->setModel(mm);
    ModelRenderer::getInstance()->render(plane, *program);
}

const std::shared_ptr<BlurStage> &BlurStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<BlurStage>(new BlurStage);
    }

    return instance;
}