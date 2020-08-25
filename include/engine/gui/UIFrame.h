#ifndef UIFRAME_H
#define UIFRAME_H

#include <engine/math/Vec3.h>
#include <engine/gui/Primitives/PrimitiveRenderer.h>
#include <engine/gui/Primitives/Rectangle.h>
#include "UIComposite.h"

class UIFrame : public UIComposite {
private:
    bool cursorOver = false;
public:
    explicit UIFrame(const std::shared_ptr<Shape> &shape);
    UIFrame(const std::shared_ptr<UIFrame> &frame);

    UIFrame(UIFrame *frame);

    bool isCursorOver() const;

    void cursor(const double &x, const double &y) override;
    void draw() override;
};

#endif // UIFRAME_H