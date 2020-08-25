#ifndef UISTAGE_H
#define UISTAGE_H

#include <memory>
#include <engine/core/FreeCamera.h>
#include "engine/gui/UIComponent.h"
#include "UIRenderer.h"

class UIStage {
protected:
    std::shared_ptr<UIComponent> rootComponent;
public:
    UIStage();

    virtual void click(const double &x, const double &y);
    virtual void cursor(const double &x, const double &y);
    virtual void renderUI();
    virtual void renderContent(FreeCamera &camera, double dt) = 0;
};



#endif // UISTAGE_H
