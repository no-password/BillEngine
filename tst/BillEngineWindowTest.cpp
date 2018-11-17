#include "BillEngineWindow.h"

#include "BillEngine.h"
#include <iostream>
#include <cstdlib>
#include <cassert>

#define HEIGHT 200
#define WIDTH  400
#define TITLE  "I do not like green eggs and ham, I do not like them, Sam I Am"

#define REFRESH_COUNT 100

BillEngineWindow* window = nullptr;

static void before() {
	if (BillEngine::init() != 0) {
		std::cerr << "Failed to init BillEngine" << std::endl;
		exit(1);
	}

	window = new BillEngineWindow(HEIGHT, WIDTH, TITLE, true);
	window->render();
}

static void after() {
	delete window;
}

static void ResizeTest() {
	std::cout << "[ResizeTest]" << std::endl;
	const int NEW_H = 400;
	const int NEW_W = 600;
	window->reshape(NEW_W, NEW_H);
	assert(window->getWidth() == NEW_W);
	assert(window->getHeight() == NEW_H);
}

static void ContextTest() {
	std::cout << "[ContextTest]" << std::endl;
	BillEngineWindow* second = new BillEngineWindow(HEIGHT, WIDTH, TITLE, false);
	assert(second != nullptr);
	second->render();

	second->setContext();
	window->setContext();

	second->close();
	delete second;
}

static void RoutineTest() {
	std::cout << "[RoutineTest]" << std::endl;
	/* immitate state where event causes window close */
	int counter = 0;
	while (! window->shouldClose()) {
		counter++;
		BillEngine::clearPreviousBuffer();
		window->swapBuffers();
		window->poll();
		if (counter >= REFRESH_COUNT) {
			break;
		}
	}
}

int main(int argc, char** argv) {
	std::cout << "START: " << argv[0] << std::endl;
	before();
	ResizeTest();
	ContextTest();
	RoutineTest();
	after();
	std::cout << "FINISHED: " << argv[0] << std::endl;
}
