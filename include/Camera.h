#ifndef CAMERA_H_INCLUDED
#define CAMERA_H

#include "common.h"
#include "Geometry.h"

#include <unordered_map>

#define CAMERA_VELOCITY 0.05f

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
		void look();

		void lookFirstPerson();
		void lookTopDown();

		void moveBasedOnKeyPressMap(const std::unordered_map<int, bool>* keyPressMap /*pointer b/c do not want to copy this*/);
		void rotateFocalPointAboutPositionHorizontal(double angle);

		void moveForwardRelative(double velocity);
		void moveBackwardRelative(double velocity);
		void moveLeftRelative(double velocity);
		void moveRightRelative(double velocity);
};

#endif
