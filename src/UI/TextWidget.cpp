#include "TextWidget.h"
#include "../Globals.h"

void TextWidget::layout(NVGcontext *ctx) {
    nvgFontSize(ctx, fontSize * Globals::pxRatio);
    nvgFontFace(ctx, "sans");

    float tw = nvgTextBounds(ctx, 0, 0, text.c_str(), nullptr, nullptr);

    width = tw;
    height = fontSize;
}

void TextWidget::setText(std::string text) {
    this->text = text;
}

void TextWidget::draw(NVGcontext *ctx) {
    Widget::draw(ctx);
    nvgFontSize(ctx, fontSize * Globals::pxRatio);
    nvgFontFace(ctx, "sans");
    nvgFillColor(ctx, nvgRGB(255, 255, 255));

    nvgText(ctx, 0, fontSize, text.c_str(), nullptr);
}