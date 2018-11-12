#ifndef CAMERA_H_INCLUDED
#define CAMERA_H

#include "common.h"
#include "Geometry.h"

#include <unordered_map>

class Camera {
	private:
		Camera() {
			angle = 0.0f;
		}
	
	public:
		Point3D focalPoint;
		Point3D position;
		Point3D upDirection;
		GLfloat angle;

		static Camera* getCamera();
		void lookFirstPerson();
		void lookTopDown();

		void moveBasedOnKeyPressMap(const std::unordered_map<int, bool>* keyPressMap /*pointer b/c do not want to copy this*/);
};

#endif
