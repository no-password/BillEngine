#include "BillEngineWindow.h"

#include <GLFW/glfw3.h>

BillEngineWindow::BillEngineWindow(int widthIn, int heightIn, std::string titleIn) {
	width = widthIn;
	height = heightIn;
	title = titleIn;

	glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
}

int BillEngineWindow::getWidth() {
	return width;
}

int BillEngineWindow::getHeight() {
	return height;
}
