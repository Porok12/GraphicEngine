#include "UIFrameDecorator.h"


UIFrameDecorator::UIFrameDecorator(const std::shared_ptr<UIFrame> &frame) : UIFrame(frame) {

}

UIFrameDecorator::UIFrameDecorator(UIFrame *frame) : UIFrame(frame) {
    this->frame.reset(frame);
}

void UIFrameDecorator::draw(float offsetX, float offsetY) {
    UIFrame::draw(offsetX, offsetY);
    PrimitiveRenderer::getInstance()->render(new Rectangle(frame->getShape()->x,frame->getShape()->y,20,20));
}
