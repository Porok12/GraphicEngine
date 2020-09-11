#include <engine/gui/UIFrameDecorator.h>

UIFrameDecorator::UIFrameDecorator(const std::shared_ptr<UIFrame> &frame) : UIFrame(frame) {

}

UIFrameDecorator::UIFrameDecorator(UIFrame *frame) : UIFrame(frame) {
    this->frame.reset(frame);
}

void UIFrameDecorator::draw() {
    UIFrame::draw();
    if (auto rect = std::dynamic_pointer_cast<Rectangle>(shape)) {
        auto ptr = std::make_shared<Rectangle>(rect->x+rect->w-20, rect->y, 20, rect->h);
        PrimitiveRenderer::getInstance()->setOffset(fVec3(0, 0, 0))->setColor(0, 1, 0)->render(ptr);
    }
}
