#include "BresenhamStage.h"

std::shared_ptr<BresenhamStage> BresenhamStage::instance = nullptr;
//GLuint BresenhamStage::CANVAS_WIDTH = 1024;
//GLuint BresenhamStage::CANVAS_HEIGHT = 1024;

BresenhamStage::BresenhamStage()
        : dirLight(fVec3(0.02), fVec3(1), fVec3(1), fVec3(-0.2f, -1.0f, -0.5f)), //dirLight(fVec3(0.05), fVec3(0.5), fVec3(0.8f), fVec3(-0.2f, -1.0f, -0.5f)),
          pointLight(fVec3(0.1), fVec3(1), fVec3(1), fVec3(0.0f, 0.0f, 0.0f), 1.0f, 0.14f, 0.07f), pixels({}) {

    auto rect2 = std::make_shared<Rectangle>(10, 10, 250, 500);
    auto composite2 = std::make_shared<UIFrame>(new UIFrameDecorator(new UIFrame(rect2)));
    {
        std::shared_ptr<UIComponent> component = std::make_shared<UIButton>("Menu", 10, 10, 100, 50);
        temp = component;
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint)->setY(new FixedConstraint(500 - 50 - 10)));
        composite2->add(component);

        component = std::make_shared<UISelectBox>(10, 70, 150, 50);
        std::dynamic_pointer_cast<UISelectBox>(component)->setOptions({"Line", "Circle", "Elipse", "Fill area"});
        std::dynamic_pointer_cast<UISelectBox>(component)->addChangedCallback([this](int i){
            switch (i) {

            }
        });
        component->setConstraints((new RectangleConstraints())
                                          ->setX(new CenterConstraint)
                                          ->setY(new FixedConstraint(10)));
        composite2->add(component);
    }

    composite2->update(800, 600);
    rootComponent = composite2;

    plane.enableBumpMapping(true);
    plane.loadModel(ResourceLoader::getPath("plane4.obj", MODEL));

    program = std::make_shared<ShaderProgram>("bresenham");

//    int width, height, nrComponents;
//    unsigned char * data = SOIL_load_image(ResourceLoader::getPath("test.bmp", TEXTURE).c_str(),
//            &width, &height, &nrComponents, 0);
//
//    if (data) {
//        GLenum format = GL_RED;
//        if (nrComponents == 1)
//            format = GL_RED;
//        else if (nrComponents == 3)
//            format = GL_RGB;
//        else if (nrComponents == 4)
//            format = GL_RGBA;
//
//        glBindTexture(GL_TEXTURE_2D, textureID);
//        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        SOIL_free_image_data(data);
//    }

    pixels.fill(255);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CANVAS_WIDTH, CANVAS_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

//    std::array<GLubyte, 1024 * 1024 * 3> pixels {};
//    pixels.fill(0);
//    glBindTexture(GL_TEXTURE_2D, textureID);
//    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
//    glGenerateMipmap(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 0);

//    int width, height, nrComponents;
//    unsigned char * data = SOIL_load_image(ResourceLoader::getPath("test.bmp", TEXTURE).c_str(),
//            &width, &height, &nrComponents, 0);
//    SOIL_free_image_data(data);


//    std::array<GLubyte, 300 * 300 * 3> pixels { };
//    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 200, 200, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

    std::cout << "Bresenham" << std::endl;
    auto points = Bresenham().getLine(iVec2(0, 0), iVec2(10, 10));
//    std::cout << points.size() << std::endl;
//    for (const auto &p: points) {
//        std::cout << p.x << " " << p.y << std::endl;
//    }

//    std::cout << "Bresenham" << std::endl;
//    auto points = Bresenham().getCircle(iVec2(0, 0), 10);
//    std::cout << points.size() << std::endl;
//    for (const auto &p: points) {
//        std::cout << p.x << " " << p.y << std::endl;
//    }

//    std::cout << "Bresenham" << std::endl;
//    auto points = Bresenham().getElipse(iVec2(0, 0), 10, 10);
//    std::cout << points.size() << std::endl;
//    for (const auto &p: points) {
//        std::cout << p.x << " " << p.y << std::endl;
//    }

    InputHandler::addCursorPositionListener([this](const double &mouse_x, const double &mouse_y) {
        GLint data[4];
        glGetIntegerv(GL_VIEWPORT, data);

//        double x = (2.0f * mouse_x) / data[2] - 1.0f;
//        double y = (2.0f * mouse_y) / data[3] - 1.0f;
        double x = 1.0f - (2.0f * mouse_x) / data[2];
        double y = 1.0f - (2.0f * mouse_y) / data[3];
        double z = 1.0f;
        fVec3 ray_nds = fVec3(x, y, z);
//        std::cout << ray_nds.x << " " << ray_nds.y << " " << ray_nds.z << "\n";

        fVec4 ray_clip = fVec4(ray_nds.x, ray_nds.y, -1.0, 1.0);
//        std::cout << ray_clip.x << " " << ray_clip.y << " " << ray_clip.z << "\n";

        Mat4 projection_matrix = ModelRenderer::getInstance()->getProjection();
        projection_matrix.inverse();
        Mat4 view_matrix = ModelRenderer::getInstance()->getView();
        view_matrix.inverse();

//        Mat4 test = view_matrix * ModelRenderer::getInstance()->getView();
//        for (int i = 0; i < 4; i++) {
//            for (int j = 0; j < 4; j++) {
//                std::cout << test[i][j] << " ";
//            }
//            std::cout << "\n";
//        }

        fVec4 ray_eye = projection_matrix * ray_clip;
        ray_eye = fVec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
//        std::cout << ray_eye.x << " " << ray_eye.y << " " << ray_eye.z << "\n";

        fVec4 tmp = view_matrix * ray_eye;
        fVec3 ray_wor = fVec3(tmp.x, tmp.y, tmp.z);
        ray_wor.normalize();

//        std::cout << ray_wor.x << " " << ray_wor.y << " " << ray_wor.z << "\n";
        fVec3 ray_origin(0);
        if (cam) {
            ray_origin = cam->getPos();
            ray_origin.x = -ray_origin.x;
            ray_origin.y = -ray_origin.y;
//            std::cout << ray_origin.x << " " << ray_origin.y << " " << ray_origin.z << "\n";
//            std::cout << cam->getFront().x << " " << cam->getFront().y << " " << cam->getFront().z << "\n";
        }

        fVec3 normal(0, 0, 1);
        fVec3 center(0, 0, -8);

        fVec3 point(0);
        if (Raycaster::raycastPlane(ray_origin, ray_wor, normal, center, point)) {
            std::cout << point.x << " " << point.y << " " << point.z << "\n";
            int x = (2.0 - (1.0 + point.y / 5)) * CANVAS_WIDTH / 2;
            int y = (2.0 - (1.0 + point.x / 5)) * CANVAS_HEIGHT / 2;
//            int x = (0.0 + (1.0 + point.y / 5)) * CANVAS_WIDTH / 2;
//            int y = (0.0 + (1.0 + point.x / 5)) * CANVAS_HEIGHT / 2;

            if (x > 0 && x < CANVAS_WIDTH && y > 0 && y < CANVAS_HEIGHT) {
                pixels[(x+y*CANVAS_WIDTH)*3+0] = 0;
                pixels[(x+y*CANVAS_WIDTH)*3+1] = 0;
                pixels[(x+y*CANVAS_WIDTH)*3+2] = 0;

                glBindTexture(GL_TEXTURE_2D, textureID);
                glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
                glGenerateMipmap(GL_TEXTURE_2D);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        }
    });
}

void BresenhamStage::renderUI() {
    UIStage::renderUI();
}

void BresenhamStage::renderContent(FreeCamera &camera, double dt) {
    program->use();
    program->set3f("viewPos", camera.getPos());
    if (!cam) {
        cam = std::shared_ptr<FreeCamera>(&camera);
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

//    std::array<GLubyte, 1 * 1 * 4> pixels { 0 };
//    glReadPixels(0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
//    for (const auto &p: pixels) {
//        std::cout << (int) p << std::endl;
//    }

//    std::array<GLubyte, 800 * 600 * 4> pixels { };
//    pixels.fill(255);
//    glDrawPixels(800, 600, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

    Mat4 view = camera.getViewMatrix();
    ModelRenderer::getInstance()->setView(view);
    Mat4 mm = Mat4::identity();
    mm = Mat4::translate(0, 0, -8) * mm;
    ModelRenderer::getInstance()->setModel(mm);
    ModelRenderer::getInstance()->render(plane, *program);
}

const std::shared_ptr<BresenhamStage> &BresenhamStage::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<BresenhamStage>(new BresenhamStage);
    }

    return instance;
}
