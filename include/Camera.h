#ifndef CAMERA_H_INCLUDED
#define CAMERA_H

#include "common.h"
#include "Geometry.h"

class Camera {
	private:
		Camera() {
		}
	
	public:
		Point3D focalPoint;
		Point3D position;
		Point3D upDirection;

		static Camera* getCamera();
};

#endif
