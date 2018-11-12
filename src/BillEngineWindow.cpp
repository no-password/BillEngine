#include "BillEngineWindow.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "Camera.h"

Point2D previousMousePosition;

BillEngineWindow::BillEngineWindow(int widthIn, int heightIn, std::string titleIn) {
	width = widthIn;
	height = heightIn;
	title = titleIn;

	glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	glfwSetWindowSizeCallback(glfwWindow, reshape);
	glfwSetFramebufferSizeCallback(glfwWindow, framebufferSize);
	framebufferSize(glfwWindow, width, height);
	reshape(glfwWindow, width, height);

	double mouseX, mouseY;
	glfwGetCursorPos(glfwWindow, &mouseX, &mouseY);
	previousMousePosition.x = mouseX;
	previousMousePosition.y = mouseY;
	glfwSetCursorPosCallback(glfwWindow, mouseLookCallback);
}

void BillEngineWindow::render() {
	framebufferSize(glfwWindow, width, height);
	reshape(glfwWindow, width, height);
}

int BillEngineWindow::getWidth() {
	return width;
}

int BillEngineWindow::getHeight() {
	return height;
}

bool BillEngineWindow::windowShouldClose() {
	return glfwWindowShouldClose(glfwWindow);
}

/* reshape callback */
void BillEngineWindow::reshape(GLFWwindow *w, int width, int height)
{  
	std::cout << "reshape" << std::endl;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, width/(float)height, 1, 10);
  glMatrixMode(GL_MODELVIEW);
}

/* fb callback */
void BillEngineWindow::framebufferSize(GLFWwindow *w, int width, int height)
{  
  glViewport(0, 0, width, height);
	std::cout << "fb" << std::endl;
}

void BillEngineWindow::swapBuffers() {
	glfwSwapBuffers(glfwWindow);
}

void BillEngineWindow::setContext() {
	glfwMakeContextCurrent(glfwWindow);
}

void BillEngineWindow::setControlScheme(ControlScheme *scheme) {
	glfwSetKeyCallback(glfwWindow, scheme->keyboardCallback);
}

void BillEngineWindow::mouseLookCallback(GLFWwindow *w, double xpos, double ypos) {
	Camera* camera = Camera::getCamera();
	double dMouseX = previousMousePosition.x - xpos;
	double dMouseY = previousMousePosition.y - ypos;

	/* Set the focal point to the origin, rotate about the origin, translate the positin back */
	if (dMouseX != 0) {
		std::cout << "Here!" << std::endl;
		double theta = dMouseX > 0 ? -1.0f : 1.0f;
		double camFocAtOriginX = camera->focalPoint.x - camera->position.x;
		double camFocAtOriginZ = camera->focalPoint.z - camera->position.z;

		double newCamFocAtOriginX = camFocAtOriginZ * sin(d2r(theta)) + camFocAtOriginX * cos(d2r(theta));
		double newCamFocAtOriginZ = camFocAtOriginZ * cos(d2r(theta)) - camFocAtOriginX * sin(d2r(theta));

		camera->focalPoint.x = newCamFocAtOriginX + camera->position.x;
		camera->focalPoint.z = newCamFocAtOriginZ + camera->position.z;
		camera->angle += theta;
	}
	std::cout << "mouse callback old: \nX: " << previousMousePosition.x <<
	"\nY: " << previousMousePosition.y << std::endl;

	previousMousePosition.x = xpos;
	previousMousePosition.y = ypos;
	
	std::cout << "mouse callback new: \nX: " << previousMousePosition.x <<
	"\nY: " << previousMousePosition.y << std::endl;
}
