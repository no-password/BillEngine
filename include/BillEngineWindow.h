#ifndef BILLENGINEWINDOW_H_INCLUDED
#define BILLENGINEWINDOW_H

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

		bool windowShouldClose();

		static void reshape(GLFWwindow *w, int width, int height);
		static void framebufferSize(GLFWwindow *w, int width, int height);
};

#endif
