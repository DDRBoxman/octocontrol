#include "VectorButtonWidget.h"

VectorButtonWidget::VectorButtonWidget(int width, int height, std::function<void(NVGcontext*)> drawFunc) :
        drawFunc(drawFunc) {
    this->width = width;
    this->height = height;
}

void VectorButtonWidget::draw(NVGcontext *ctx) {
    Widget::draw(ctx);
    drawFunc(ctx);
}

void VectorButtonWidget::mouseButtonEvent(int mouseX, int mouseY, int button, int action) {
    printf("%d, %d\n", mouseX, mouseY);
}