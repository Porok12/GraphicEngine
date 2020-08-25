#include "engine/gui/UIFrame.h"

UIFrame::UIFrame(const std::shared_ptr<Shape> &shape) : UIComposite(shape) {

}

UIFrame::UIFrame(const std::shared_ptr<UIFrame> &frame) : UIComposite(frame->shape) {

}

UIFrame::UIFrame(UIFrame *frame) : UIComposite(frame->shape) {

}

void UIFrame::draw() {
    PrimitiveRenderer::getInstance()->setColor(fVec3(0.2f, 0.5f, 0.8f))->setOffset(fVec3(getOffset().x, getOffset().y, 0))->render(shape);
    UIComposite::draw();
}

void UIFrame::cursor(const double &x, const double &y) {
    cursorOver = shape->contains(x, y);
    UIComposite::cursor(x, y);
}

bool UIFrame::isCursorOver() const {
    return cursorOver;
}
