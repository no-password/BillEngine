#ifndef BILLENGINEWINDOW_H_INCLUDED
#define BILLENGINEWINDOW_H

#include "common.h"
#include "ControlScheme.h"

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

		/* OpenGL activly renders one buffer. and draws to another one in the backgroud */
		void swapBuffers();

		void setContext();

		void render();

		void setControlScheme(ControlScheme *scheme);

		static void reshape(GLFWwindow *w, int width, int height);
		static void framebufferSize(GLFWwindow *w, int width, int height);
};

#endif
