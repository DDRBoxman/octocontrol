#pragma once

#include <functional>
#include "Widget.h"

class VectorButtonWidget : public Widget {

private:
    std::function<void(NVGcontext*)> drawFunc;

public:
    VectorButtonWidget(int width, int height, std::function<void(NVGcontext*)> drawFunc);

    void draw(NVGcontext *ctx);

    void mouseButtonEvent(int mouseX, int mouseY, int button, int action);
};