#include "UIFrameDecorator.h"


UIFrameDecorator::UIFrameDecorator(const std::shared_ptr<UIFrame> &frame) : UIFrame(frame) {

}

UIFrameDecorator::UIFrameDecorator(UIFrame *frame) : UIFrame(frame) {
    this->frame.reset(frame);
}

void UIFrameDecorator::draw() {
    UIFrame::draw();
//    PrimitiveRenderer::getInstance()->render(new Rectangle(frame->getShape()->x,frame->getShape()->y,20,20));
    auto ptr = std::shared_ptr<Shape>(new Circle(frame->getShape()->x,frame->getShape()->y, 20));
    PrimitiveRenderer::getInstance()->render(ptr);
}
