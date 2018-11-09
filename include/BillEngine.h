#ifndef BILLENGINE_H_INCLUDED
#define BILLENGIN_H

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

	public:
		/**
		 * Initialize OpenGL, amongst other things
		 */
		static void init();

		/**
		 * Set the floor texture
		 */
		static int setFloorTexture(std::string path);

		/**
		 * Set the floor height
		 */
		static int setFloorHeight(GLfloat height);

		/**
		 * Launch a map
		 */
		static int launchMap(BillEngineMap *map);

		/**
		 * Close the current map
		 */
		static int closeMap();
};


#endif
