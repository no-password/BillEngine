#ifndef BILLENGINE_H_INCLUDED
#define BILLENGINE_H

#include "common.h"
#include "BillEngineMap.h"

#define DEFAULT_FLOOR_HEIGHT 0.0f

class BillEngine {
	private:
		BillEngine() {}

		//floor texture
		static GLfloat floorHeight;
		static BillEngineMap* currentMap;

		/* Auxillary methods */
		static void initOpenGL();

		static void initGlew();

		/* For adding/removing things from memory table */
		static void addMemoryObject(MemoryObject *memObject);
		static void removeMemoryObject(MemoryObject *memObject);

	public:
		/**
		 * Initialize OpenGL, amongst other things
		 */
		static int init();

		/**
		 * Set the floor texture
		 */
		static int setFloorTexture(std::string path);

		/**
		 * Set the floor height
		 */
		static int setFloorHeight(GLfloat height);
		static GLfloat getFloorHeight();

		/**
		 * Launch a map
		 */
		static int launchMap(BillEngineMap *map);

		/**
		 * Close the current map
		 */
		static int closeMap();

		static void drawFloor();

		static void clearPreviousBuffer();

		/**
		 * Increment the frame counter, amongst other things 
		 */
		static void nextFrame();

		static float getFPS();

		
};


#endif
