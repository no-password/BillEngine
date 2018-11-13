#ifndef BILLENGINEWINDOW_H_INCLUDED
#define BILLENGINEWINDOW_H

#include "common.h"
#include "ControlScheme.h"
#include "Geometry.h"

class BillEngineWindow {
	private:
		int width;
		int height;
		std::string title;
		GLFWwindow *glfwWindow;

	public:
		BillEngineWindow(int widthIn, int heightIn, std::string title);
		/* reshape this window */
		int reshape(int widht, int height);
		int getWidth();
		int getHeight();

		/* determine if window should close */
		bool windowShouldClose();

		/* OpenGL activly renders one buffer. and draws to another one in the backgroud */
		void swapBuffers();

		/* Set the current context to this window */
		void setContext();

		/* tell the window to start rendering stuff */
		void render();

		/* Set the control scheme used in the window */
		void setControlScheme(ControlScheme *scheme);

		/* Close the window */
		void closeWindow();

		/* Poll user input */
		void poll();
};

#endif
