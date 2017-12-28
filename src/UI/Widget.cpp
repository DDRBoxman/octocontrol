#include "Widget.h"

void Widget::draw(NVGcontext *ctx) {
    nvgSave(ctx);
    nvgTranslate(ctx, x, y);

    for (auto child : children) {
        nvgSave(ctx);
        nvgTranslate(ctx, child->x, child->y);
        child->draw(ctx);
        nvgRestore(ctx);
    }
    nvgRestore(ctx);
}

void Widget::layout(NVGcontext *ctx) {
    int offset = 0;
    int height = 0;
    int width = 0;
    for (auto child : children) {
        child->layout(ctx);
        child->y = offset;
        offset += child->height + padding;
        height += child->height + padding;
        if (child->width > width) {
            width = child->width;
        }
    }
}

void Widget::addChild(Widget *child) {
    children.push_back(child);
}

void Widget::mouseButtonEvent(int mouseX, int mouseY, int button, int action) {
    for (auto child : children) {
        int relx = mouseX - x - child->x;
        int rely = mouseY - y - child->y;

        if (relx >= 0 && relx < child->width && rely >= 0 && rely < child->height) {
            child->mouseButtonEvent(relx, rely, button, action);
        }
    }
}
