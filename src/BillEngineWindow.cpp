#include "BillEngineWindow.h"

#include <GLFW/glfw3.h>
#include <iostream>

BillEngineWindow::BillEngineWindow(int widthIn, int heightIn, std::string titleIn) {
	width = widthIn;
	height = heightIn;
	title = titleIn;

	glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	glfwSetWindowSizeCallback(glfwWindow, reshape);
	glfwSetFramebufferSizeCallback(glfwWindow, framebufferSize);
	framebufferSize(glfwWindow, width, height);
	reshape(glfwWindow, width, height);
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
