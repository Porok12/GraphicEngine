#include "UISelectBox.h"

void UISelectBox::addClickCallback(std::function<void()> onClick) {
    this->onClick = std::move(onClick);
}

void UISelectBox::addCursorCallback(std::function<void(UISelectBox*)> &onCoursor) {
    this->onCursor = onCoursor;
}

void UISelectBox::addChangedCallback(std::function<void(int)> onChanged) {
    this->onChanged = onChanged;
}

void UISelectBox::draw() {
//    PrimitiveRenderer::getInstance()
//            ->setColor(backgroundColor)
//            ->setOffset(fVec3(getOffset().x, getOffset().y, 0))
//            ->render(shape);
//    FontRenderer::getInstance()->setPosition(shape->x+getOffset().x, shape->y+getOffset().y)
//            .setScale(0.5f)
//            .setTextBox(shape->getTextBox())
//            .render("1");

    fVec2 offset = getOffset() + fVec2(shape->x, shape->y);

    PrimitiveRenderer::getInstance()
            ->setColor(backgroundColor)
            ->setOffset(fVec3(offset.x, offset.y, 0))
            ->render(option->shape);
    FontRenderer::getInstance()->setPosition((float)offset.x, (float)offset.y)
            .setScale(0.5f)
            .setTextBox(shape->getTextBox())
            .render(option->text);


    if (opened) {
        offset += fVec2(0, -option->shape->h);
        for (const auto &opt: options) {
            if (option == opt)
                continue;
            PrimitiveRenderer::getInstance()
                    ->setColor(opt->over ? fVec3(1.0) : fVec3(0.5))
                    ->setOffset(fVec3(offset.x, offset.y, 0))
                    ->render(opt->shape);
            FontRenderer::getInstance()->setPosition(opt->shape->x+offset.x, opt->shape->y+offset.y)
                    .setScale(0.5f)
                    .setTextBox(shape->getTextBox())
                    .render(opt->text);
            offset += fVec2(0, -opt->shape->h);
        }
    }

//    fVec2 offset = fVec2(0, 0);
//    for (const auto &opt: options) {
//        PrimitiveRenderer::getInstance()
//                ->setColor(opt->over ? fVec3(1.0) : fVec3(0.5))
//                ->setOffset(fVec3(offset.x, offset.y, 0))
//                ->render(opt->shape);
//        FontRenderer::getInstance()->setPosition(opt->shape->x+offset.x, opt->shape->y+offset.y)
//                .setScale(0.5f)
//                .setTextBox(shape->getTextBox())
//                .render(opt->text);
//        if (!opened)
//            break;
//    }

//    if (opened) {
//        fVec2 offset = fVec2(0, 0); //getOffset() + fVec2(shape->x, shape->y);
//        for (const auto &opt: options) {
////            offset -= fVec2(0, 40);
//            PrimitiveRenderer::getInstance()
//                    ->setColor(opt->over ? fVec3(1.0) : fVec3(0.5))
//                    ->setOffset(fVec3(offset.x, offset.y, 0))
//                    ->render(opt->shape);
//            FontRenderer::getInstance()->setPosition(opt->shape->x+offset.x, opt->shape->y+offset.y)
//                    .setScale(0.5f)
//                    .setTextBox(shape->getTextBox())
//                    .render(opt->text);
//        }
//    }

//    for (const auto &btn: options) {
//        btn->draw();
//    }
};

void UISelectBox::click(const double &x, const double &y) {
    if (opened) {
        fVec2 offset = getOffset() + fVec2(shape->x, shape->y);
        if (option->shape->contains(x-offset.x, y-offset.y)) {
            option = option;
            opened = false;
            return;
        }
        offset += fVec2(0, -option->shape->h);

        for (const auto &opt: options) {
            if (option == opt)
                continue;

            if (opt->shape->contains(x-offset.x, y-offset.y)) {
                option = opt;
                opened = false;
                if (onChanged) {
                    onChanged(getOption());
                }
            }
            offset += fVec2(0, -opt->shape->h);
        }
    }

    if (shape->contains(x, y)) {
        opened = !opened;
        if(onClick) {
            onClick();
        }
    }
}

void UISelectBox::cursor(const double &x, const double &y) {
    if (shape->contains(x, y)) {
        if(onCursor) {
            onCursor(this);
        }
        this->backgroundColor = fVec3(1.0f);
    } else {
        this->backgroundColor = fVec3(0.5f);
    }

    if (opened) {
        fVec2 offset = getOffset() + fVec2(shape->x, shape->y);
        option->over = option->shape->contains(x-offset.x, y-offset.y);
        offset += fVec2(0, -option->shape->h);

        for (const auto &opt: options) {
            if (option == opt)
                continue;

            opt->over = opt->shape->contains(x-offset.x, y-offset.y);
            offset += fVec2(0, -opt->shape->h);
        }
    }
}

void UISelectBox::setBackgroundColor(const fVec3 &backgroundColor) {
    UISelectBox::backgroundColor = backgroundColor;
}

void UISelectBox::setOptions(const std::vector<std::string> &options) {
//    std::vector<std::string> vec = {options...};

    for (int i = 0; i < options.size(); ++i) {
//        this->options.push_back(std::make_shared<Option>(shape->x, shape->y - i*shape->h, shape->w, shape->h, options[i]));
        this->options.push_back(std::make_shared<Option>(0, 0, shape->w, shape->h, options[i]));
    }

    option = this->options[0];
//    for (auto a: options) {
//
//    }
}

int UISelectBox::getOption() {
    for (int i = 0; i < options.size(); ++i) {
        if (option == options[i]) {
            return i;
        }
    }
    throw std::out_of_range("");
}
