#include "BillEngine.h"

#include <iostream>
#include <cstdlib>

static void before() {
	std::cout << "[Draw Routine Test]" << std::endl;
	if (BillEngine::init() != 0) {
		std::cout << "Failed to initialize engine" << std::endl;
		exit(EXIT_FAILURE);
	}
}

static void drawRoutineTest() {
	BillEngine::clearPreviousBuffer();
	BillEngine::drawFloor();
	BillEngine::nextFrame();
	BillEngine::getFPS();
}

int main(int argc, char** argv) {
	std::cout << "STARTING: " << argv[0] << std::endl;
	before();
	drawRoutineTest();
	std::cout << "FINISHED: " << argv[0] << std::endl;
	return 0;
}
