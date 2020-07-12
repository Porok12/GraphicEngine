#ifndef UISTAGEMANAGER_H
#define UISTAGEMANAGER_H

#include <memory>
#include <core/Camera.h>
#include "UIStage.h"
#include "UIRenderer.h"

enum Stages {
    MENU,
    MESH,
    PARTICLES
};

class UIStageManager {
private:
    double deltaTime;
    Camera camera;
    std::shared_ptr<UIStage> rootUI;

public:
    UIStageManager();

    void setStage(Stages stage);
    void update(Camera camera, double dt);
    void render();

    void click(const double &x, const double &y);
    void cursor(const double &x, const double &y);
};

#endif // UISTAGEMANAGER_H