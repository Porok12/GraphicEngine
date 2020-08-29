#include <engine/gui/UIFrame.h>
#include <engine/gui/UISelectBox.h>
#include <engine/gui/UIFrameDecorator.h>
#include <engine/core/models/Model.h>
#include <engine/core/algorithm/carpet/CreateEngine.h>
#include <engine/core/models/ModelRenderer.h>
#include <engine/core/light/Materials.h>
#include "SierpinskiStage.h"

std::shared_ptr<SierpinskiStage> SierpinskiStage::instance = nullptr;

SierpinskiStage::SierpinskiStage() :
        dirLight(fVec3(1.0), fVec3(1.0), fVec3(1.0f), fVec3(-0.2f, -1.0f, -0.5f)) {
    auto rect2 = std::make_shared<Rectangle>(10, 10, 200, 300);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 10, 10, 100, 50);
        temp = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint)->setY(new FixedConstraint(300 - 50 - 10)));
        composite2->add(component);
    }

    composite2->update(800, 600);
    rootComponent = composite2;

    program = std::make_shared<ShaderProgram>("light");

    ModelGenerator modelGenerator;
//    auto vertices = modelGenerator.generateCube();
//    cube = modelGenerator.fromVertices(vertices);
    std::vector<std::vector<Vertex>> cubes;
    modelGenerator.menger(3, 0, 0, 0, 1, cubes);
    std::vector<Mesh> meshes;
    for (auto &c: cubes) {
        meshes.emplace_back(c);
    }
//    std::cerr << meshes[10].vertices[0].Position.x << std::endl;
    cube = Model(meshes);
    cube.useFlatNormals(true);
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

void SierpinskiStage::renderContent(FreeCamera &camera, double dt) {
    Mat4 view = camera.getViewMatrix();
    Mat4 mm = Mat4::identity();
    mm = Mat4::translate(0, 0, -4) * mm;

    program->use();
    program->set3f("material.ambient", GOLD.ambient);
    program->set3f("material.diffuse", GOLD.diffuse);
    program->set3f("material.specular", GOLD.specular);
    program->set1f("material.shininess", GOLD.shininess);
    program->set3f("viewPos", camera.getPos());

    program->set1b("dir", true);
    program->set1b("point", false);
    program->set1b("spot", false);

    light(program.get(), "dirLight", dirLight);

    ModelRenderer::getInstance()->setModel(mm);
    ModelRenderer::getInstance()->setView(view);
    ModelRenderer::getInstance()->render(cube, *program);

    FontRenderer::getInstance()->setPosition(700, 0).render(std::to_string(1/dt));
}