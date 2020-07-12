#ifndef UISTAGE_H
#define UISTAGE_H

#include <memory>
#include <core/Camera.h>
#include "UIComponent.h"
#include "UIRenderer.h"

class UIStage {
protected:
    std::shared_ptr<UIComponent> rootComponent;
public:
    UIStage();

//    UIStage(const std::shared_ptr<UIComponent> &rootComponent);

    virtual void click(const double &x, const double &y);
    virtual void cursor(const double &x, const double &y);
    virtual void renderUI();
    virtual void renderContent(Camera camera, double dt) = 0;
};



#endif // UISTAGE_H
