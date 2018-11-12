#include "common.h"
#include "BillEngine.h"
#include "BillEngineWindow.h"
#include "Camera.h"

#include <iostream>
#include <unordered_map>
#include <cstdlib>

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

	BillEngineWindow* win = new BillEngineWindow(800, 600, "window");
	win->setContext();
	Camera *cam = Camera::getCamera();
	unsigned long frame = 0;
	win->render();
	ControlScheme *controls = ControlScheme::getControlScheme();
	controls->setCallback(keyboard);
	std::unordered_map<int, bool>* keyPressMap = &(controls->keyPressMap);
	win->setControlScheme(controls);
	while (!win->windowShouldClose()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		gluLookAt(
			cam->position.x, cam->position.y, cam->position.z,
			cam->focalPoint.x, cam->focalPoint.y, cam->focalPoint.z,
			cam->upDirection.x, cam->upDirection.y, cam->upDirection.z
		);

		glPushMatrix();
		BillEngine::drawFloor();
		glPopMatrix();
		win->swapBuffers();
		glfwPollEvents();
		cam->moveBasedOnKeyPressMap(keyPressMap);
		frame++;
		if (frame % 1000 == 0) {
			std::cout << "Frame: " << frame<< std::endl;
		}
	}

	return 0;
}

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
	ControlScheme *controls = ControlScheme::getControlScheme();
	std::unordered_map<int, bool>* keyPressMap = &(controls->keyPressMap);

	std::cout << "Key: " << key << std::endl;

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
