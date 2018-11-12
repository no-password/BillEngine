#include "ControlScheme.h"

ControlScheme* instance = nullptr;

ControlScheme* ControlScheme::getControlScheme() {
	if (instance == nullptr) {
		instance = new ControlScheme();
	}

	return instance;
}

void ControlScheme::setCallback(void (*keyboard)(GLFWwindow*, int, int, int, int)) {
	instance->keyboardCallback = keyboard;
}
