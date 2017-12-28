#include <iostream>
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
#include "nanovg.h"
#define NANOVG_GL2_IMPLEMENTATION
#include "nanovg_gl.h"
#include "UI/Widget.h"
#include "UI/TextWidget.h"
#include "UI/ButtonWidget.h"
#include "Globals.h"
#include "UI/VectorButtonWidget.h"

int backgroundImage;

Widget *baseWidget;
double mx, my;

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int modifiers) {
    baseWidget->mouseButtonEvent(mx,my, button, action);
}

void loadImages(NVGcontext* vg) {
	backgroundImage = nvgCreateImage(vg, "./resources/background.jpg", 0);
}

void cleanupImages(NVGcontext* vg) {
	nvgDeleteImage(vg, backgroundImage);
}

void renderBackground(NVGcontext* vg, float width, float height) {
	nvgSave(vg);

	int w, h;
	nvgImageSize(vg, backgroundImage, &w, &h);

	NVGpaint imgPaint = nvgImagePattern(vg, 0, 0, width, height, 0.0f/180.0f*NVG_PI, backgroundImage, 1.0f);
	nvgBeginPath(vg);
	nvgRect(vg, 0, 0, width, height);
	nvgFillPaint(vg, imgPaint);
	nvgFill(vg);

	nvgBeginPath(vg);
	nvgRect(vg, 0, 0, width, height);
	nvgFillColor(vg, nvgRGBA(186, 0, 0, 192));
	nvgFill(vg);

	nvgRestore(vg);
}

void renderUI(NVGcontext* ctx, float mx, float my, float width, float height) {
	renderBackground(ctx, width, height);

    baseWidget->draw(ctx);
}

int render3d() {

	//glTranslatef(0.0f,0.0f,-1.1f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-10, 10, -10, 10, 0, 10);
	glFrustum(-1, 1, -1, 1, 0.1f, 10);
	glTranslatef(0.0f,0.0f,-0.5f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glRotatef(0.5f, 0.f, 1.f, 0.f);
	//glTranslatef(0.0f, 0.0f, 0.5f);

	glBegin( GL_QUADS );
	glVertex2f( -0.5f, -0.5f );
	glVertex2f( 0.5f, -0.5f );
	glVertex2f( 0.5f, 0.5f );
	glVertex2f( -0.5f, 0.5f );
	glEnd();

}

int main() {
	GLFWwindow* window;
	NVGcontext* vg = nullptr;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		printf("Failed to init GLFW.");
		return -1;
	}

	window = glfwCreateWindow(320, 240, "octocontrol", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);

    glfwSetMouseButtonCallback(window, mouse_button_callback);

	glfwMakeContextCurrent(window);

	vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);

	if (vg == nullptr) {
		printf("Could not init nanovg.\n");
		return -1;
	}

	glfwSwapInterval(0);

	glfwSetTime(0);

	loadImages(vg);

    float font = nvgCreateFont(vg, "sans", "resources/fonts/Roboto-Regular.ttf");

    if (font == -1) {
        printf("Could not load font.\n");
        return -1;
    }

    int winWidth, winHeight;
    int fbWidth, fbHeight;

    glfwGetWindowSize(window, &winWidth, &winHeight);
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

    // Calculate pixel ration for hi-dpi devices.
    Globals::pxRatio = (float)fbWidth / (float)winWidth;

    baseWidget = new Widget();
    auto test = new TextWidget();
    test->setText("Test");
    baseWidget->addChild(test);
    auto testButton = new ButtonWidget();
    testButton->setText("Test Button");
    baseWidget->addChild(testButton);

    auto menuButton = new VectorButtonWidget(36, 36, [] (NVGcontext *ctx) {
        nvgBeginPath(ctx);
        nvgStrokeColor(ctx, nvgRGB(255, 255, 255));
        nvgStrokeWidth(ctx, 1);
        nvgCircle(ctx, 10, 16, 4);
        nvgCircle(ctx, 20, 16, 4);
        nvgCircle(ctx, 30, 16, 4);
        nvgStroke(ctx);
    });
    baseWidget->addChild(menuButton);

    baseWidget->layout(vg);


	while (!glfwWindowShouldClose(window)) {


		glfwGetCursorPos(window, &mx, &my);
		glfwGetWindowSize(window, &winWidth, &winHeight);
		glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

		glViewport(0, 0, fbWidth, fbHeight);

		glClearColor(0,0,0,0);

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

		nvgBeginFrame(vg, winWidth, winHeight, Globals::pxRatio);

		renderUI(vg, mx, my, winWidth, winHeight);

		nvgEndFrame(vg);

		//render3d();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	cleanupImages(vg);

	nvgDeleteGL2(vg);

	glfwTerminate();
	return 0;
}