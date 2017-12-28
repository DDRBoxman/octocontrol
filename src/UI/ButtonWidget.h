#pragma once

#include <string>

#include "Widget.h"

class ButtonWidget : public Widget {

private:
    std::string text;
    int fontSize = 12;

public:
    void layout(NVGcontext *ctx);

    void setText(std::string text);

    void draw(NVGcontext *ctx);
};
