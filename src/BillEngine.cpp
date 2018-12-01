#include "BillEngine.h"
#include "Color.h"

#include <iostream>
#include <cstdio>

GLfloat BillEngine::floorHeight = DEFAULT_FLOOR_HEIGHT;
BillEngineMap *BillEngine::currentMap = nullptr;
MemoryTable* BillEngine::memTable = nullptr;
auto startTime = Time::now();
unsigned long frameCounter = 1;

static const float FLOOR_DIM_X = 20.0f;
static const float FLOOR_DIM_Y = 20.0f;
static const float FLOOR_TILE_SIZE = 0.3f;
static const Color BLUE(0.15f, 0.15f, 0.7f);
static const Color GREEN(0.15f, 0.7f, 0.15f);

int BillEngine::init() {
	initOpenGL();
	initGlew();
	if (!glfwInit()) {
		return -1;
	}

	startTime = Time::now();

	memTable = MemoryTable::getInstance();

	return 0;
}

void BillEngine::addMemoryObject(MemoryObject *memObject, size_t size) {
	memTable->put(memObject, size);
}

void BillEngine::removeMemoryObject(MemoryObject *memObject) {
	memTable->remove(memObject);
}

void BillEngine::updateMemoryObjectSize(MemoryObject *memObject) {
	memTable->update(memObject);
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
    gluPerspective(PERS_DEF_ANGLE, PERS_DEF_ASPECT, PERS_DEF_NEAR, PERS_DEF_FAR);
    glMatrixMode(GL_MODELVIEW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
}

void BillEngine::clearPreviousBuffer() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void BillEngine::initGlew() {
	glewInit();
	glewExperimental = GL_TRUE;
}

void BillEngine::nextFrame() {
	frameCounter++;
}

float BillEngine::getFPS() {
	auto currentTime = Time::now();
	fsec timeDelta = currentTime - startTime;
	return frameCounter / timeDelta.count();
}

/* render the 'floor' */
void BillEngine::drawFloor()
{
	glPushMatrix();
	float i,j;
	char flag = 0;
	for (i = -FLOOR_DIM_X; i < FLOOR_DIM_X; i+=FLOOR_TILE_SIZE)
	{
		for (j = -FLOOR_DIM_Y; j < FLOOR_DIM_Y; j+=FLOOR_TILE_SIZE)
		{
			if (flag == 0)
				glColor3f(BLUE.R, BLUE.G, BLUE.B);
			else
				glColor3f(GREEN.R, GREEN.G, GREEN.B);
			flag = flag == 0 ? 1 : 0;
			glBegin(GL_QUADS);
			glVertex3f(i, floorHeight, j);
			glVertex3f(i, floorHeight, j + 1.0f);
			glVertex3f(i + 1.0f, floorHeight, j + 1.0f);
			glVertex3f(i + 1.0f, floorHeight, j);
			glEnd();
		}
		flag = flag == 0 ? 1 : 0;
	}
	glPopMatrix();
}

int BillEngine::setFloorHeight(GLfloat height) {
	floorHeight = height;
	return 0;
}

GLfloat BillEngine::getFloorHeight() {
	return floorHeight;
}
