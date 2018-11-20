#include "BillEngineWindow.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "Camera.h"

Point2D previousMousePosition;
void reshapeCallback(GLFWwindow *w, int width, int height);
void framebufferSize(GLFWwindow *w, int width, int height);
void mouseLookCallback(GLFWwindow *w, double xpos, double ypos);

BillEngineWindow::BillEngineWindow(int widthIn, int heightIn, std::string titleIn, bool setContext) {
	width = widthIn;
	height = heightIn;
	title = titleIn;

	glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	glfwSetWindowSizeCallback(glfwWindow, reshapeCallback);
	glfwSetFramebufferSizeCallback(glfwWindow, framebufferSize);

	double mouseX, mouseY;
	glfwGetCursorPos(glfwWindow, &mouseX, &mouseY);
	previousMousePosition.x = mouseX;
	previousMousePosition.y = mouseY;
	glfwSetCursorPosCallback(glfwWindow, mouseLookCallback);
	if (setContext) {
		this->setContext();
	}
}

size_t BillEngineWindow::getSize() const {
	return sizeof(BillEngineWindow);
}

/* Need to call framebuffer/reshape callbacks in order to get the window to initially display something */
void BillEngineWindow::render() {
	framebufferSize(glfwWindow, width, height);
	reshapeCallback(glfwWindow, width, height);
}

int BillEngineWindow::getWidth() {
	return width;
}

int BillEngineWindow::getHeight() {
	return height;
}

int BillEngineWindow::reshape(int width, int height) {
	reshapeCallback(glfwWindow, width, height);
	this->width = width;
	this->height = height;

	return 0;
}

bool BillEngineWindow::shouldClose() {
	return glfwWindowShouldClose(glfwWindow);
}

void BillEngineWindow::poll() {
	glfwPollEvents();
}

/* reshape callback */
void reshapeCallback(GLFWwindow *w, int width, int height)
{  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, width/(float)height, 1, 10);
  glMatrixMode(GL_MODELVIEW);
}

/* fb callback */
void framebufferSize(GLFWwindow *w, int width, int height)
{  
  glViewport(0, 0, width, height);
}

void BillEngineWindow::swapBuffers() {
	glfwSwapBuffers(glfwWindow);
}

void BillEngineWindow::setContext() {
	glfwMakeContextCurrent(glfwWindow);
	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void BillEngineWindow::setControlScheme(ControlScheme *scheme) {
	glfwSetKeyCallback(glfwWindow, scheme->keyboardCallback);
}

/**
 * Callback function used for mouselook
 * */
void mouseLookCallback(GLFWwindow *w, double xpos, double ypos) {
	Camera* camera = Camera::getCamera();
	double dMouseX = previousMousePosition.x - xpos;
	double dMouseY = previousMousePosition.y - ypos;

	/* Set the focal point to the origin, rotate about the origin, translate the positin back */
	if (dMouseX != 0) {
		double theta = dMouseX > 0 ? 1.5f : -1.5f;
		camera->rotateFocalPointAboutPositionHorizontal(theta);
	}

	if (dMouseY != 0) {
		double theta = dMouseY < 0 ? 1.5f : -1.5f;
		camera->rotateFocalPointAboutPositionVertical(theta);
	}
	previousMousePosition.x = xpos;
	previousMousePosition.y = ypos;
}

void BillEngineWindow::close() {
	glfwSetWindowShouldClose(glfwWindow, GLFW_TRUE);
}
