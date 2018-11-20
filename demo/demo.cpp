#include "common.h"
#include "BillEngine.h"
#include "BillEngineWindow.h"
#include "Camera.h"
#include "MemoryTable.h"

#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <chrono>

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
	if (BillEngine::init() != 0) {
		std::cout << "Problem initializing engine" << std::endl;
		return 1;
	}

	if (glGetError() != GL_NO_ERROR) {
		std::cout << "OpenGL error" << std::endl;
		return 1;
	}

	/* Create a new window and make said window in focus */
	BillEngineWindow* win = new BillEngineWindow(800, 600, "window", true);
	win->setContext();

	/* get the camera */
	Camera *cam = Camera::getCamera();

	/* tell the window it needs to render */
	win->render();

	/* get the current control scheme and set the keyboard callback */
	ControlScheme *controls = ControlScheme::getControlScheme();
	controls->setCallback(keyboard);

	/* Camera knows how to act based on keypress map */
	std::unordered_map<int, bool>* keyPressMap = &(controls->keyPressMap);

	/* Set the window to use the current control scheme */
	win->setControlScheme(controls);

	MemoryTable* memTable = MemoryTable::getInstance();

	while (!win->shouldClose()) {
		/* clear the previous draw buffer */

		BillEngine::clearPreviousBuffer();
		/* tell the camera to look where we want it to look */
		cam->look();

		/* draw things */
		BillEngine::drawFloor();
		
		/* swap the draw buffer and poll */
		win->swapBuffers();
		win->poll();

		/* move the camera based on keypressMap*/
		cam->moveBasedOnKeyPressMap(keyPressMap);
		
		/* measure frames per second */
		BillEngine::nextFrame();
		//float FPS = BillEngine::getFPS();
		//std::cout << "FPS: " << FPS << std::endl;
		memTable->dump(std::cout);
	}

	return 0;
}

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
	ControlScheme *controls = ControlScheme::getControlScheme();
	std::unordered_map<int, bool>* keyPressMap = &(controls->keyPressMap);

	switch (action) {
		case (GLFW_PRESS):
			if (key == GLFW_KEY_ESCAPE) {
				exit(EXIT_SUCCESS);
			}
			keyPressMap->insert_or_assign(key, true);
			break;

		case (GLFW_RELEASE):
			keyPressMap->insert_or_assign(key, false);
			break;
	}
}
