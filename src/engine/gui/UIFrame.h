#ifndef UIFRAME_H
#define UIFRAME_H

#include <math/Vec3.h>
#include <gui/Primitives/PrimitiveRenderer.h>
#include <gui/Primitives/Rectangle.h>
#include "UIComposite.h"

class UIFrame : public UIComposite {
public:
    UIFrame(const std::shared_ptr<Shape> &shape);
    UIFrame(const std::shared_ptr<UIFrame> &frame);
    UIFrame(UIFrame *frame);

    void draw() override;
};

#endif // UIFRAME_H