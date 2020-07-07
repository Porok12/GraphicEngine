#ifndef UIFRAMEDECORATOR_H
#define UIFRAMEDECORATOR_H

#include <memory>
#include "UIFrame.h"

class UIFrameDecorator : public UIFrame {
protected:
    std::shared_ptr<UIFrame> frame;
public:
    UIFrameDecorator(const std::shared_ptr<UIFrame> &frame);
    UIFrameDecorator(UIFrame *frame);

    void draw(float offsetX, float offsetY) override;
};

#endif // UIFRAMEDECORATOR_H


