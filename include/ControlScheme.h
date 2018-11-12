#ifndef CONTROLSCHEME_H_INCLUDED
#define CONTROLSCHEME_H

#include "common.h"
#include <unordered_map>

class ControlScheme {
	private:
		ControlScheme() {
			keyboardCallback = nullptr;
		}
	public:
		void (*keyboardCallback)(GLFWwindow*, int, int, int, int);
		void setCallback(void (*keyboard)(GLFWwindow*, int, int, int, int));
		static ControlScheme* getControlScheme();

		std::unordered_map<int, bool> keyPressMap;
};

#endif
