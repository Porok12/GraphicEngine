#include "BlurStage.h"

std::shared_ptr<BlurStage> BlurStage::instance = nullptr;

BlurStage::BlurStage() {

    auto rect2 = std::make_shared<Rectangle>(10, 10, 120, 250);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 10, 10, 100, 50);
        temp = component;
        composite2->add(component);

        component = std::make_shared<UIButton>("Reset", 10, 70, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){});
        //program = std::make_shared<ShaderProgram>("gaussian");
        composite2->add(component);

        component = std::make_shared<UIButton>("Normal", 10, 130, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){});
        composite2->add(component);

        component = std::make_shared<UIButton>("Spec", 10, 190, 100, 50);
        std::dynamic_pointer_cast<UIButton>(component)->addClickCallback([this](){});
        composite2->add(component);
    }

    rootComponent = composite2;

    plane.enableBumpMapping(false);
    plane.loadModel(ResourceLoader::getPath("plane.obj", MODEL));

    blur = std::make_shared<ShaderProgram>("gaussian");
    program = std::make_shared<ShaderProgram>("final_gaussian");
    textureID = ResourceLoader::loadTexture("grid.png");

    glGenFramebuffers(2, pingpongFBO);
    glGenTextures(2, pingpongColorbuffers);

    for (unsigned int i = 0; i < 2; i++) {
        glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
        glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 800, 600, 0, GL_RGBA, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            BOOST_LOG_TRIVIAL(error) << "Framebuffer not complete!";
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void BlurStage::renderUI() {
    UIStage::renderUI();
}

void BlurStage::renderContent(Camera camera, double dt) {
    Mat4 view = camera.getViewMatrix();
    ModelRenderer::getInstance()->setView(view);


    blur->use();
    bool horizontal = true;
    glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
    blur->set1b("horizontal", horizontal);
    glBindTexture(GL_TEXTURE_2D, textureID);//pingpongColorbuffers[!horizontal]);
    drawQuad();

    horizontal = false;
    glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
    blur->set1b("horizontal", horizontal);
    glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);
    drawQuad();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    program->use();
    program->set3f("viewPos", camera.getPos());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[0]);
    Mat4 mm = Mat4::identity();
    mm = Mat4::translate(0, -2, -4) * mm;
    ModelRenderer::getInstance()->setModel(mm);
    ModelRenderer::getInstance()->render(plane, *program);
}

const std::shared_ptr<BlurStage> &BlurStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<BlurStage>(new BlurStage);
    }

    return instance;
}

void BlurStage::drawQuad() {
    if (quadVAO == 0) {
        float quadVertices[] = {
                -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };

        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) nullptr);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    }

//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
