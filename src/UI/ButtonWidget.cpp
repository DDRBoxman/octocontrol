#include "ButtonWidget.h"
#include "../Globals.h"

void ButtonWidget::layout(NVGcontext *ctx) {
    nvgFontSize(ctx, fontSize * Globals::pxRatio);
    nvgFontFace(ctx, "sans");

    float tw = nvgTextBounds(ctx, 0, 0, text.c_str(), nullptr, nullptr);

    width = tw + (padding * 2);
    height = fontSize + (padding * 2);
}

void ButtonWidget::setText(std::string text) {
    this->text = text;
}

void ButtonWidget::draw(NVGcontext *ctx) {
    Widget::draw(ctx);

    nvgFontSize(ctx, fontSize * Globals::pxRatio);

    nvgFontFace(ctx, "sans");
    nvgFillColor(ctx, nvgRGB(255, 255, 255));

    nvgText(ctx, padding, fontSize + padding, text.c_str(), nullptr);

    nvgBeginPath(ctx);
    nvgRect(ctx, 0, 0, width, height);
    nvgStrokeColor(ctx, nvgRGB(255, 255, 255));
    nvgStroke(ctx);
}