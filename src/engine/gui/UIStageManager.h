#ifndef UISTAGEMANAGER_H
#define UISTAGEMANAGER_H

#include <memory>
#include <core/Camera.h>
#include "UIRenderer.h"
#include "MeshStage.h"
#include "MenuStage.h"
#include "ParticlesStage.h"
#include "LightStage.h"

enum Stages {
    MENU,
    MESH,
    PARTICLES,
    LIGHT
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