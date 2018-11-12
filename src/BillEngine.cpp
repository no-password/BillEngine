#include "BillEngine.h"

#include <iostream>
#include <cstdio>

GLfloat BillEngine::floorHeight = DEFAULT_FLOOR_HEIGHT;
BillEngineMap *BillEngine::currentMap = nullptr;

int BillEngine::init() {
	initOpenGL();
	initGlew();
	if (!glfwInit()) {
		return -1;
	}

	return 0;
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

void BillEngine::initGlew() {
	glewInit();
	glewExperimental = GL_TRUE;
}

/* render the 'floor' */
void BillEngine::drawFloor()
{
	float i,j;
	char flag = 0;
	for (i = -20.0f; i < 20.0f; i+=1.0f)
	{
		for (j = -20.0f; j < 20.0f; j+=1.0f)
		{
			if (flag == 0)
				glColor3f(0.15f, 0.15f, 0.7f);
			else
				glColor3f(0.15f, 0.7f, 0.15f);
			flag = flag == 0 ? 1 : 0;
			glBegin(GL_QUADS);
			glVertex3f(i, floorHeight, j);
			glVertex3f(i, floorHeight, j + 1.0f);
			glVertex3f(i + 1.0f, floorHeight, j + 1.0f);
			glVertex3f(i + 1.0f, floorHeight, j);
			glEnd();
			//printf("Floor: i = %f, j = %f\n", i, j);
		}
		flag = flag == 0 ? 1 : 0;
	}
}

int BillEngine::setFloorHeight(GLfloat height) {
	floorHeight = height;
	return 0;
}

GLfloat BillEngine::getFloorHeight() {
	return floorHeight;
}
