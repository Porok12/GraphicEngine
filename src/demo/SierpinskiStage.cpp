#include <engine/gui/UIFrame.h>
#include <engine/gui/UISelectBox.h>
#include <engine/gui/UIFrameDecorator.h>
#include <engine/core/models/Model.h>
#include <engine/core/algorithm/VertexGenerator.h>
#include <engine/core/models/ModelRenderer.h>
#include <engine/core/light/Materials.h>
#include <engine/gui/UILabel.h>
#include "SierpinskiStage.h"

std::shared_ptr<SierpinskiStage> SierpinskiStage::instance = nullptr;

SierpinskiStage::SierpinskiStage() :
        dirLight(fVec3(1.0), fVec3(1.0), fVec3(1.0f), fVec3(-0.2f, -1.0f, -0.5f)),
        pointLight(fVec3(1.0f), fVec3(1.0f), fVec3(1.0f), fVec3(0.0f, 0.0f, 0.0f), 1.0f, 0.14f, 0.07f),
        spotLight(fVec3(1.0), fVec3(1.0), fVec3(1.0f), fVec3(0), fVec3(0), 0.91f, 0.82f, 1.0f, 0.07f, 0.017f)
{
    const int HEIGHT = 580;
    const int WIDTH = 200;
    auto rect2 = std::make_shared<Rectangle>(10, 10, WIDTH, HEIGHT);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 10, 10, 100, 50);
        temp = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint)->setY(new FixedConstraint(HEIGHT - 50 - 10)));
        composite2->add(component);

        component = std::make_shared<UISelectBox>(10, 10, 150, 50);
        std::dynamic_pointer_cast<UISelectBox>(component)->setOptions({"Pyramid", "Cube", "Swowflake"});
        std::dynamic_pointer_cast<UISelectBox>(component)->addChangedCallback([this](int option){
            algorithmIterations = 0;
            std::dynamic_pointer_cast<UILabel>(iterLabel)->setText(std::to_string(algorithmIterations));

            algorithmSelect = option;
            updateMesh();
        });

        std::dynamic_pointer_cast<UISelectBox>(component)->setConstraints(
                (new RectangleConstraints())->setX(new CenterConstraint())->setY(new FixedConstraint(80)));
        composite2->add(component);

        std::shared_ptr<UIComponent> label = std::make_shared<UILabel>("0.00 FPS", 10, 400);
        std::dynamic_pointer_cast<UILabel>(label)->setColor(iVec3(255, 0, 0));
        label->setConstraints((new RectangleConstraints())
                                      ->setX(new FixedConstraint(WIDTH+50))
                                      ->setY(new FixedConstraint(HEIGHT-25)));
        composite2->add(label);
        minLabel = label;

        label = std::make_shared<UILabel>("0.00 FPS", 10, 400);
        std::dynamic_pointer_cast<UILabel>(label)->setColor(iVec3(0, 255, 0));
        label->setConstraints((new RectangleConstraints())
                                      ->setX(new FixedConstraint(WIDTH+50))
                                      ->setY(new FixedConstraint(HEIGHT-50)));
        composite2->add(label);
        maxLabel = label;

        label = std::make_shared<UILabel>("0.00 FPS", 10, 400);
        std::dynamic_pointer_cast<UILabel>(label)->setColor(iVec3(255, 255, 255));
        label->setConstraints((new RectangleConstraints())
                                      ->setX(new FixedConstraint(WIDTH+50))
                                      ->setY(new FixedConstraint(HEIGHT-75)));
        composite2->add(label);
        fpsLabel = label;

        label = std::make_shared<UILabel>("0", 10, 400);
        label->setConstraints((new RectangleConstraints())
                                      ->setX(new CenterConstraint())
                                      ->setY(new FixedConstraint(30)));
        composite2->add(label);
        iterLabel = label;

        label = std::make_shared<UILabel>("1 elements", 10, 400);
        label->setConstraints((new RectangleConstraints())
                                      ->setX(new FixedConstraint(120))
                                      ->setY(new FixedConstraint(-40)));
        composite2->add(label);
        meshesLabel = label;

        component.reset(new UIButton("<", 40, 40, 40, 40));
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(10))
                                          ->setY(new FixedConstraint(10)));
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){
            if (algorithmIterations > 0) {
                algorithmIterations--;
                std::dynamic_pointer_cast<UILabel>(iterLabel)
                        ->setText(std::to_string(algorithmIterations));
                updateMesh();
            }
        });
        composite2->add(component);

        component.reset(new UIButton(">", 40, 40, 40, 40));
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(150))
                                          ->setY(new FixedConstraint(10)));
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){
            if (algorithmIterations <= maxIterations) {
                algorithmIterations++;
                std::dynamic_pointer_cast<UILabel>(iterLabel)
                        ->setText(std::to_string(algorithmIterations));
                updateMesh();
            }
        });
        composite2->add(component);

        component.reset(new UISlider(50, 500, 100, 20, 1, 90, 1));
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(20))
                                          ->setY(new FixedConstraint(250)));
        std::dynamic_pointer_cast<UISlider>(component)->addChangedCallback([this](float f){
            x = f;
        });
        composite2->add(component);

        component.reset(new UISlider(50, 500, 100, 20, 1, 90, 1));
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(20))
                                          ->setY(new FixedConstraint(280)));
        std::dynamic_pointer_cast<UISlider>(component)->addChangedCallback([this](float f){
            y = f;
        });
        composite2->add(component);

        component.reset(new UISlider(50, 500, 100, 20, 1, 90, 1));
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(20))
                                          ->setY(new FixedConstraint(310)));
        std::dynamic_pointer_cast<UISlider>(component)->addChangedCallback([this](float f){
            z = f;
        });
        composite2->add(component);

        component.reset(new UISlider(50, 500, 100, 20, 0, 300, 1));
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(20))
                                          ->setY(new FixedConstraint(340)));
        std::dynamic_pointer_cast<UISlider>(component)->addChangedCallback([this](float f){
            speed = f;
        });
        composite2->add(component);

        label = std::make_shared<UILabel>("x", 10, 400);
        label->setConstraints((new RectangleConstraints())
                                      ->setX(new FixedConstraint(140))
                                      ->setY(new FixedConstraint(258)));
        composite2->add(label);

        label = std::make_shared<UILabel>("y", 10, 400);
        label->setConstraints((new RectangleConstraints())
                                      ->setX(new FixedConstraint(140))
                                      ->setY(new FixedConstraint(288)));
        composite2->add(label);

        label = std::make_shared<UILabel>("z", 10, 400);
        label->setConstraints((new RectangleConstraints())
                                      ->setX(new FixedConstraint(140))
                                      ->setY(new FixedConstraint(318)));
        composite2->add(label);

        label = std::make_shared<UILabel>("speed", 10, 400);
        label->setConstraints((new RectangleConstraints())
                                      ->setX(new FixedConstraint(160))
                                      ->setY(new FixedConstraint(348)));
        composite2->add(label);

        // RGB

        int tmp = 40;

        component.reset(new UISlider(50, 500, 100, 20, 0, 1, 0.01));
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(20))
                                          ->setY(new FixedConstraint(370+tmp)));
        std::dynamic_pointer_cast<UISlider>(component)->addChangedCallback([this](float f){
            r = f;
        });
        std::dynamic_pointer_cast<UISlider>(component)->setValue(1);
        composite2->add(component);

        component.reset(new UISlider(50, 500, 100, 20, 0, 1, 0.01));
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(20))
                                          ->setY(new FixedConstraint(400+tmp)));
        std::dynamic_pointer_cast<UISlider>(component)->addChangedCallback([this](float f){
            g = f;
        });
        composite2->add(component);

        component.reset(new UISlider(50, 500, 100, 20, 0, 1, 0.01));
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new FixedConstraint(20))
                                          ->setY(new FixedConstraint(430+tmp)));
        std::dynamic_pointer_cast<UISlider>(component)->addChangedCallback([this](float f){
            b = f;
        });
        composite2->add(component);

        label = std::make_shared<UILabel>("R", 10, 400);
        label->setConstraints((new RectangleConstraints())
                                      ->setX(new FixedConstraint(140))
                                      ->setY(new FixedConstraint(378+tmp)));
        composite2->add(label);

        label = std::make_shared<UILabel>("G", 10, 400);
        label->setConstraints((new RectangleConstraints())
                                      ->setX(new FixedConstraint(140))
                                      ->setY(new FixedConstraint(408+tmp)));
        composite2->add(label);

        label = std::make_shared<UILabel>("B", 10, 400);
        label->setConstraints((new RectangleConstraints())
                                      ->setX(new FixedConstraint(140))
                                      ->setY(new FixedConstraint(438+tmp)));
        composite2->add(label);
    }

    composite2->update(800, 600);
    addRoot(composite2);

    program = std::make_shared<ShaderProgram>("sierpinski");

    updateMesh();
}

const std::shared_ptr<SierpinskiStage> &SierpinskiStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<SierpinskiStage>(new SierpinskiStage);
    }

    return instance;
}

void SierpinskiStage::renderUI() {
    UIStage::renderUI();
}

void light(ShaderProgram *program, std::string name, DirectionalLight dirLight) {
    program->set3f(name+".direction", dirLight.getDirection());
    program->set3f(name+".ambient", dirLight.getAmbient());
    program->set3f(name+".diffuse", dirLight.getDiffuse());
    program->set3f(name+".specular", dirLight.getSpecular());
}

void light(ShaderProgram *program, std::string name, PointLight pointLight) {
    program->set3f(name+".position", pointLight.getPosition());
    program->set1f(name+".constant", pointLight.getConstant());
    program->set1f(name+".linear", pointLight.getLinear());
    program->set1f(name+".quadratic", pointLight.getQuadratic());
    program->set3f(name+".ambient", pointLight.getAmbient());
    program->set3f(name+".diffuse", pointLight.getDiffuse());
    program->set3f(name+".specular", pointLight.getSpecular());
}

void light(ShaderProgram *program, std::string name, SpotLight spotLight) {
    program->set3f(name+".position", spotLight.getPosition());
    program->set3f(name+".direction", spotLight.getDirection());
    program->set1f(name+".cutOff", spotLight.getCutOff());
    program->set1f(name+".outerCutOff", spotLight.getOuterCutOff());
    program->set1f(name+".constant", spotLight.getConstant());
    program->set1f(name+".linear", spotLight.getLinear());
    program->set1f(name+".quadratic", spotLight.getQuadratic());
    program->set3f(name+".ambient", spotLight.getAmbient());
    program->set3f(name+".diffuse", spotLight.getDiffuse());
    program->set3f(name+".specular", spotLight.getSpecular());
}

void updateMaterial(ShaderProgram *program, Material &material, float r, float g, float b) {
    material.ambient.x = r * 0.05; material.ambient.y = g * 0.05; material.ambient.z = b * 0.05;
    material.diffuse.x = r * 0.85; material.diffuse.y = g * 0.85; material.diffuse.z = b * 0.85;
    material.specular.x = r; material.specular.y = g; material.specular.z = b;

    program->set3f("material.ambient", material.ambient);
    program->set3f("material.diffuse", material.diffuse);
    program->set3f("material.specular", material.specular);
    program->set1f("material.shininess", material.shininess);
}

void SierpinskiStage::renderContent(FreeCamera &camera, double dt) {
    now += dt * speed;

    Mat4 view = camera.getViewMatrix();
    Mat4 mm = Mat4::identity();
    mm = Mat4::translate(0, 0, -8) * mm;
    mm = Mat4::rotation(now, fVec3(x, y, z)) * mm;
//    mm = Mat4::rotation(x, fVec3(1, 0, 0)) *
//         Mat4::rotation(y, fVec3(0, 1, 0)) *
//         Mat4::rotation(z, fVec3(0, 0, 1)) *
//         mm;

//    tmpLoad += dt * 0.4;
//    tmp.x = 1.2 * std::sin(tmpLoad);
//    tmp.z = -4.0;
//    pointLight.setPosition(tmp);

    dirLight.setSpecular(fVec3(0.3));
    dirLight.setAmbient(fVec3(0.3));
    dirLight.setDiffuse(fVec3(0.3));

    spotLight.setPosition(camera.getPos());
    spotLight.setDirection(camera.getFront());

    program->use();
    updateMaterial(program.get(), material, r, g, b);
    program->set3f("viewPos", camera.getPos());

    program->set1b("dir", true);
    program->set1b("point", false);
    program->set1b("spot", true);

    light(program.get(), "dirLight", dirLight);
//    light(program.get(), "pointLight", pointLight);
    light(program.get(), "spotLight", spotLight);


    ModelRenderer::getInstance()->setModel(mm);
    ModelRenderer::getInstance()->setView(view);
//    ModelRenderer::getInstance()->render(cube, *program);
    ModelRenderer::getInstance()->render(iCube, *program);

    buffer += dt;
    minMaxBuffer += dt;
    frames++;

    if (buffer >= 1.0) {
        fps = frames;
        buffer = 0;
        frames = 0;
    }

    if (minMaxBuffer >= 10.0) {
        minMaxBuffer = 0;
        fpsMax = 0;
        fpsMin = 100;
    }

    fpsMax = (fpsMax < fps) ? fps : fpsMax;
    fpsMin = (fpsMin > fps) ? fps : fpsMin;

    static std::stringstream ss;
    ss.str(std::string());
    ss << (int)fpsMin << " FPS";
    std::dynamic_pointer_cast<UILabel>(minLabel)->setText(ss.str());
    ss.str(std::string());
    ss << (int)fpsMax << " FPS";
    std::dynamic_pointer_cast<UILabel>(maxLabel)->setText(ss.str());
    ss.str(std::string());
//    if (fps < 10.0) ss << "0";
    ss << (int)fps << " FPS";
    std::dynamic_pointer_cast<UILabel>(fpsLabel)->setText(ss.str());
}

void SierpinskiStage::updateMesh() {
    VertexGenerator modelGenerator;
    std::vector<Vertex> iVertices;
    std::vector<fVec3> positions;

    switch (algorithmSelect) {
        case 0: {
            maxIterations = 12;
            modelGenerator.instancedPyramid(algorithmIterations, 0, 0, 0, 8, iVertices, positions);
            break;
        }
        case 1: {
            maxIterations = 6;
            modelGenerator.instancedMenger(algorithmIterations, 0, 0, 0, 2, iVertices, positions);
            break;
        }
        case 2: {
            maxIterations = 8;
            modelGenerator.instancedSnowflake(algorithmIterations, 0, 0, 0, 2, iVertices, positions);
            break;
        }
    }

    InstancedMesh iMesh;
    iMesh.loadMesh(iVertices);
    iMesh.setPositions(positions);
    iCube.loadMesh(iMesh);
    std::dynamic_pointer_cast<UILabel>(meshesLabel)->setText(std::to_string(positions.size()) + " elemets");
}
