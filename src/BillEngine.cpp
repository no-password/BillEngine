#include "BillEngine.h"

void BillEngine::init() {
	BillEngine::floorHeight = DEFAULT_FLOOR_HEIGHT;
	BillEngine::currentMap = nullptr;
	BillEngine::initOpenGL();
}

/* initialize opneGL */
void BillEngine::initOpenGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, INT_MAX);
    glMatrixMode(GL_MODELVIEW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
}
