#include "BresenhamStage.h"

std::shared_ptr<BresenhamStage> BresenhamStage::instance = nullptr;

BresenhamStage::BresenhamStage()
        : pixels({}), tmpPixels({}), startPoint(0) {

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
            option = i;
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

    pixels.fill(255);
    tmpPixels.fill(255);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CANVAS_WIDTH, CANVAS_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    InputHandler::addCursorPositionListener([this](const double &mouse_x, const double &mouse_y) {
        tmpPixels = pixels;

        fVec3 ray_wor = Raycaster::cursorToWorld(mouse_x, mouse_y);

        fVec3 ray_origin(0);
        if (cam) {
            ray_origin = cam->getPos();
            ray_origin.x = -ray_origin.x;
            ray_origin.y = -ray_origin.y;
        }

        fVec3 normal(0, 0, 1);
        fVec3 center(0, 0, -8);

        fVec3 point(0);
        if (Raycaster::raycastPlane(ray_origin, ray_wor, normal, center, point)) {
            int x = (2.0 - (1.0 + point.y / 5)) * CANVAS_WIDTH / 2;
            int y = (2.0 - (1.0 + point.x / 5)) * CANVAS_HEIGHT / 2;

            if (x > 0 && x < CANVAS_WIDTH && y > 0 && y < CANVAS_HEIGHT) {
                std::vector<iVec2> points;
                switch (option) {
                    case 0:
                        points = Bresenham().getLine(startPoint, iVec2(x, y));
                        break;
                    case 1: {
                        double dist = sqrt((double)(startPoint.x-x)*(startPoint.x-x)+(startPoint.y-y)*(startPoint.y-y));
                        points = Bresenham().getCircle(startPoint, dist);
                        break;
                    }
                    case 2:
                        points = Bresenham().getElipse(startPoint, abs(startPoint.x-x), abs(startPoint.y-y));
                        break;
                    case 3: {
                        fillPoint.x = x;
                        fillPoint.y = y;
                        break;
                    }
                    default:
                        break;
                }

                if (active) {
                    for (const auto &p: points) {
                        if (p.x > 0 && p.x < CANVAS_WIDTH && p.y > 0 && p.y < CANVAS_HEIGHT) {
                            tmpPixels[(p.x+p.y*CANVAS_WIDTH)*3+0] = 0;
                            tmpPixels[(p.x+p.y*CANVAS_WIDTH)*3+1] = 0;
                            tmpPixels[(p.x+p.y*CANVAS_WIDTH)*3+2] = 0;
                        }
                    }

                    glBindTexture(GL_TEXTURE_2D, textureID);
                    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, tmpPixels.data());
                    glGenerateMipmap(GL_TEXTURE_2D);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    glBindTexture(GL_TEXTURE_2D, 0);
                }
            }
        }
    });

    option = 0;
    active = false;
    abort = false;
    fill = false;

    InputHandler::addMouseActionListner([this](const double &mouse_x, const double &mouse_y, int btn, int act) {
        if (btn == 0 && act == 1) {
            if (std::dynamic_pointer_cast<UIFrame>(rootComponent)->isCursorOver()) {
                return;
            }

            fVec3 ray_wor = Raycaster::cursorToWorld(mouse_x, mouse_y);

            fVec3 ray_origin(0);
            if (cam) {
                ray_origin = cam->getPos();
                ray_origin.x = -ray_origin.x;
                ray_origin.y = -ray_origin.y;
            }

            static fVec3 normal(0, 0, 1); //Temporary
            static fVec3 center(0, 0, -8); //Temporary
            fVec3 point(0);

            //std::cout << ray_origin.x << " " << ray_origin.y << " " << ray_origin.z
            //          << std::endl;
            if (Raycaster::raycastPlane(ray_origin, ray_wor, normal, center, point)) {
                auto x = static_cast<int>((2.0 - (1.0 + point.y / 5)) * CANVAS_WIDTH / 2);
                auto y = static_cast<int>((2.0 - (1.0 + point.x / 5)) * CANVAS_HEIGHT / 2);

                if (x > 0 && x < CANVAS_WIDTH && y > 0 && y < CANVAS_HEIGHT) {
                    startPoint.x = x;
                    startPoint.y = y;
                }
            }
            active = true;
            abort = false;
        }

        if (btn == 0 && act == 0) {
            if (!abort) {
                pixels = tmpPixels;
            }
            active = false;
            abort = false;
        }

        if (btn == 1 && act == 1) {
            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
            glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glBindTexture(GL_TEXTURE_2D, 0);

            abort = true;
            active = false;
        }

        if (option == 3) {
            if (btn == 0 && act == 1) {
                fill = true;
                active = false;
                abort = false;
            }
        }

        if (fill) {
            fillArea(fillPoint);
            fill = false;
        }
    });

    fillColor = iVec3(255, 0, 0);
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(0, 255);
    InputHandler::addScrollOffsetListener([this, &gen, &dist](const double &x, const double &y){
        fillColor.x = dist(gen);
        fillColor.y = dist(gen);
        fillColor.z = dist(gen);
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

    instance->clear();

    return instance;
}

void BresenhamStage::fillArea(iVec2 start) {
    iVec3 bg(0);
    bg.x = tmpPixels[(start.x+start.y*CANVAS_WIDTH)*3+0];
    bg.y = tmpPixels[(start.x+start.y*CANVAS_WIDTH)*3+1];
    bg.z = tmpPixels[(start.x+start.y*CANVAS_WIDTH)*3+2];

    AreaFill::floodFill(pixels, CANVAS_WIDTH, CANVAS_HEIGHT, iVec2(start.x, start.y), fillColor, bg);

    tmpPixels = pixels;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void BresenhamStage::setFocus(bool focus) {
    this->focus = focus;
}

void BresenhamStage::clear() {
    pixels.fill(255);
    tmpPixels.fill(255);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CANVAS_WIDTH, CANVAS_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}
