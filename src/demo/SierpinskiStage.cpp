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
        dirLight(fVec3(1.0), fVec3(1.0), fVec3(1.0f), fVec3(-0.2f, -1.0f, -0.5f)),
        pointLight(fVec3(1.0f), fVec3(1.0f), fVec3(1.0f), fVec3(0.0f, 0.0f, 0.0f), 1.0f, 0.14f, 0.07f)
{
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

//    program = std::make_shared<ShaderProgram>("light");
    program = std::make_shared<ShaderProgram>("sierpinski");

    ModelGenerator modelGenerator;
////    auto vertices = modelGenerator.generateCube();
////    cube = modelGenerator.fromVertices(vertices);
//    std::vector<std::vector<Vertex>> cubes;
//    modelGenerator.menger(0, 0, 0, 0, 1, cubes);
//    std::vector<Mesh> meshes;
//    for (auto &c: cubes) {
//        meshes.emplace_back(c);
//    }
////    std::cerr << meshes[10].vertices[0].Position.x << std::endl;
//    cube = Model(meshes);
//    cube.useFlatNormals(true);

    std::vector<Vertex> iVertices;
    std::vector<fVec3> positions;
//    modelGenerator.iMenger(4, 0, 0, 0, 1, iVertices, positions);
//    modelGenerator.iPyramid(8, 0, 0, 0, 1, iVertices, positions);
    modelGenerator.iMenger2(6, 0, 0, 0, 1, iVertices, positions);
    InstancedMesh iMesh;
    iMesh.loadMesh(iVertices);
    iMesh.setPositions(positions);
    iCube.loadMesh(iMesh);
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

void SierpinskiStage::renderContent(FreeCamera &camera, double dt) {
    Mat4 view = camera.getViewMatrix();
    Mat4 mm = Mat4::identity();
    mm = Mat4::translate(0, 0, -4) * mm;

    tmpLoad += dt * 0.4;
    tmp.x = 1.2 * std::sin(tmpLoad);
    tmp.z = -4.0;
    pointLight.setPosition(tmp);

    program->use();
    Material material = YELLOW_PLASTIC;
    program->set3f("material.ambient", material.ambient);
    program->set3f("material.diffuse", material.diffuse);
    program->set3f("material.specular", material.specular);
    program->set1f("material.shininess", material.shininess);
    program->set3f("viewPos", camera.getPos());

    program->set1b("dir", true);
    program->set1b("point", true);
    program->set1b("spot", false);

    light(program.get(), "dirLight", dirLight);
    light(program.get(), "pointLight", pointLight);


    ModelRenderer::getInstance()->setModel(mm);
    ModelRenderer::getInstance()->setView(view);
//    ModelRenderer::getInstance()->render(cube, *program);
    ModelRenderer::getInstance()->render(iCube, *program);

    if (!(iter%1024)) {
        fpsMax = 0;
        fpsMin = 100;
    }

    buffer[iter++%128] = 1 / dt;
    fps = 0;
    for(int i = 0; i < 128; i++) {
        fps += buffer[i];
    }
    fps /= 128;
    fpsMax = (fpsMax < fps) ? fps : fpsMax;
    fpsMin = (fpsMin > fps) ? fps : fpsMin;


    FontRenderer::getInstance()->setPosition(700, 0).render(std::to_string(fps).substr(0, 4));
    FontRenderer::getInstance()->setPosition(700, 20).render(std::to_string(fpsMax));
    FontRenderer::getInstance()->setPosition(700, 40).render(std::to_string(fpsMin));
}