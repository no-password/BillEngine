#pragma once

#include "common.h"

class BillEngineWindow {
	private:
		int width;
		int height;
		std::string title;
		GLFWwindow *glfwWindow;
	public:
		BillEngineWindow(int widthIn, int heightIn, std::string title);
		int focus();
		int reshape(int widht, int height);
		int getWidth();
		int getHeight();
};
