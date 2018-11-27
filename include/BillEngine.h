#ifndef BILLENGINE_H
#define BILLENGINE_H

#include "common.h"
#include "MemoryObject.h"
#include "MemoryTable.h"
#include "BillEngineMap.h"

#define DEFAULT_FLOOR_HEIGHT 0.0f

class MemoryTable;
class BillEngine {

	private:
		friend MemoryObject;
		BillEngine() {}

		//floor texture
		static GLfloat floorHeight;
		static BillEngineMap* currentMap;

		/* Auxillary methods */
		static void initOpenGL();

		static void initGlew();

		/* For adding/removing things from memory table */
		static void addMemoryObject(MemoryObject *memObject, size_t size);
		static void removeMemoryObject(MemoryObject *memObject);

		static MemoryTable* memTable;

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
