#include "common.h"
#include "BillEngine.h"
#include "BillEngineWindow.h"
#include "Camera.h"

int main() {
	BillEngine::init();
	BillEngineWindow* win = new BillEngineWindow(600, 400, "window");
	Camera *cam = Camera::getCamera();
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
	}

	return 0;
}
