#include "ComboStage.h"

std::shared_ptr<ComboStage> ComboStage::instance = nullptr;

ComboStage::ComboStage()
        : dirLight(fVec3(0.3), fVec3(1), fVec3(1), fVec3(-0.2f, -1.0f, -0.5f)),
          pointLight(fVec3(0.1), fVec3(0.8), fVec3(0.8), fVec3(0.0f, 0.0f, 0.0f), 1.0f, 0.14f, 0.07f) {
    texSnowFlakes = ResourceLoader::loadTexture("SnowFlakes.png");

    auto rect2 = std::make_shared<Rectangle>(10, 10, 200, 120);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 10, 10, 100, 50);
        temp = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint)->setY(new FixedConstraint(120 - 50 - 10)));
        composite2->add(component);
    }

    model.enableBumpMapping(true);
    model.loadModel(ResourceLoader::getPath("snowman.obj", MODEL));

    plane.enableBumpMapping(true);
    plane.loadModel(ResourceLoader::getPath("untitled.obj", MODEL));
    program = std::make_shared<ShaderProgram>("texture");

    composite2->update(800, 600);
    rootComponent = composite2;
    changeGenerator(3);
}

void ComboStage::renderUI() {
    UIStage::renderUI();
}

void ComboStage::renderContent(FreeCamera &camera, double dt) {
    Mat4 view = camera.getViewMatrix();

    program->use();
    program->set3f("viewPos", camera.getPos());
    program->set1b("enableNormalMap", true);
    program->set1b("enableSpecularMap", true);
    light(program.get(), "dirLight", dirLight);
    pointLight.setPosition(fVec3(3*std::cos(b), -1, -4+3*std::sin(b)));
    b += dt;
    light(program.get(), "pointLight", pointLight);
    Mat4 mm = Mat4::identity();
    mm = Mat4::translate(0, -2, -4) * mm;
    mm = Mat4::rotationY(90) * mm;
    ModelRenderer::getInstance()->setModel(mm);
    ModelRenderer::getInstance()->setView(view);
    ModelRenderer::getInstance()->render(plane, *program);
    ModelRenderer::getInstance()->render(model, *program);

    particleGenerator->update(dt);

//    glDisable(GL_DEPTH_TEST);
    ParticleRenderer::getInstance()
            ->setRight(camera.getRight())
            ->setUp(camera.getUp())
            ->setCamera(camera.getPos())
            ->setView(view)
            ->render(particleGenerator.get());
}

const std::shared_ptr<ComboStage> &ComboStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<ComboStage>(new ComboStage);
    }

    return instance;
}

void ComboStage::changeGenerator(int i) {
    switch (i) {
        case 3:
            ParticleRenderer::getInstance()->setTexture(texSnowFlakes, 2, 2);
            particleGenerator = std::unique_ptr<ParticleGenerator>(
                    ParticleGenerator::getBuilder()
                            .setTexture(texSnowFlakes)
                            .setLifeTime(3.0)
                            .setPosition(fVec3(-2.5, 2.9, -3.0-4), fVec3(2.5, 3.5, 1.0-4))
                            .setVelocity(fVec3(-1.0, -8.0, -1.0), fVec3(1.0, -3.0, 1.0))
                            .setSelect(4)
                            .setSize(0.02, 0.1)
                            .setSpawnRate(0.05)
                            .setLimit(100)
                            .setUpdate([](double dt, const std::vector<std::shared_ptr<Particle>> &particles){
                                static std::time_t now = std::time(0);
                                static boost::random::mt19937 gen{static_cast<std::uint32_t>(now)};

                                boost::random::uniform_real_distribution<> dist{-1, 1};
                                fVec3 wind = fVec3(0);
                                if (dist(gen) < -0.85) {
                                    wind.y = dist(gen) * 10;
                                    wind.x = dist(gen) * 40;
                                    wind.z = dist(gen) * 40;
                                }

                                for (auto &p: particles) {
                                    p->LifeTime -= dt;
                                    p->Velocity += fVec3(dist(gen), -9.81f, dist(gen)) * dt * 0.001f + wind * dt;
                                    p->Position += p->Velocity * dt * 0.4;
                                }
                            }).buildPtr());
            break;
    }
}

void ComboStage::light(ShaderProgram *program, std::string name, DirectionalLight dirLight) {
    program->set3f(name+".direction", dirLight.getDirection());
    program->set3f(name+".ambient", dirLight.getAmbient());
    program->set3f(name+".diffuse", dirLight.getDiffuse());
    program->set3f(name+".specular", dirLight.getSpecular());
}

void ComboStage::light(ShaderProgram *program, std::string name, PointLight pointLight) {
    program->set3f(name+".position", pointLight.getPosition());
    program->set1f(name+".constant", pointLight.getConstant());
    program->set1f(name+".linear", pointLight.getLinear());
    program->set1f(name+".quadratic", pointLight.getQuadratic());
    program->set3f(name+".ambient", pointLight.getAmbient());
    program->set3f(name+".diffuse", pointLight.getDiffuse());
    program->set3f(name+".specular", pointLight.getSpecular());
}

