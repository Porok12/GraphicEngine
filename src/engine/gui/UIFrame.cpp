#include "UIFrame.h"

UIFrame::UIFrame(const std::shared_ptr<Shape> &shape) : UIComposite(shape) {

}

UIFrame::UIFrame(const std::shared_ptr<UIFrame> &frame) : UIFrame(frame->shape) {

}

UIFrame::UIFrame(UIFrame *frame) : UIFrame(frame->shape) {

}

void UIFrame::draw(float offsetX, float offsetY) {
    PrimitiveRenderer::getInstance()->setColor(fVec3(0.2f, 0.5f, 0.8f))->render(std::dynamic_pointer_cast<Rectangle>(shape).get());
    UIComposite::draw(0, 0);
}
