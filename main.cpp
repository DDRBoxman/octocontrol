#include <iostream>
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
#include "nanovg.h"
#define NANOVG_GL2_IMPLEMENTATION
#include "nanovg_gl.h"

int backgroundImage;

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void loadImages(NVGcontext* vg) {
	backgroundImage = nvgCreateImage(vg, "./resources/background.jpg", 0);
}

void cleanupImages(NVGcontext* vg) {
	nvgDeleteImage(vg, backgroundImage);
}

void renderMenuButton(NVGcontext* vg, int x, int y) {
	nvgSave(vg);

	nvgBeginPath(vg);
	nvgStrokeColor(vg, nvgRGB(255, 255, 255));
	nvgStrokeWidth(vg, 1);
	nvgCircle(vg, x + 10, y + 16, 4);
	nvgCircle(vg, x + 20, y + 16, 4);
	nvgCircle(vg, x + 30, y + 16, 4);
	nvgStroke(vg);

	nvgRestore(vg);
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

	nvgRestore(vg);
}

void renderUI(NVGcontext* vg, float mx, float my, float width, float height) {
	renderBackground(vg, width, height);

	renderMenuButton(vg, 280, 0);
}

int main() {
	GLFWwindow* window;
	NVGcontext* vg = NULL;

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

	glfwMakeContextCurrent(window);

	vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);

	if (vg == NULL) {
		printf("Could not init nanovg.\n");
		return -1;
	}

	glfwSwapInterval(0);

	glfwSetTime(0);

	loadImages(vg);

	while (!glfwWindowShouldClose(window)) {
		double mx, my;
		int winWidth, winHeight;
		int fbWidth, fbHeight;
		float pxRatio;

		glfwGetCursorPos(window, &mx, &my);
		glfwGetWindowSize(window, &winWidth, &winHeight);
		glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

		// Calculate pixel ration for hi-dpi devices.
		pxRatio = (float)fbWidth / (float)winWidth;

		glViewport(0, 0, fbWidth, fbHeight);

		glClearColor(0,0,0,0);

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

		nvgBeginFrame(vg, winWidth, winHeight, pxRatio);

		renderUI(vg, mx, my, winWidth, winHeight);

		nvgEndFrame(vg);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	cleanupImages(vg);

	nvgDeleteGL2(vg);

	glfwTerminate();
	return 0;
}