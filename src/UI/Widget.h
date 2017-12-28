#pragma once

#include <cstdio>
#include <vector>

#include <nanovg.h>


class Widget {

protected:
    std::vector<Widget *> children;
    int x = 0, y = 0;
    int width, height;
    int padding = 5;

public:
    virtual void draw(NVGcontext *ctx);
    virtual void layout(NVGcontext *ctx);
    virtual void mouseButtonEvent(int mouseX, int mouseY, int button, int action);
    void addChild(Widget *child);
    virtual ~Widget() = default;

};
