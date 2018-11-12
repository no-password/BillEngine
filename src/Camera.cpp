#include "Camera.h"

static Camera* instance = nullptr;

Camera* Camera::getCamera() {
	if (instance == nullptr) {
		instance = new Camera();
	}

	instance->focalPoint.x = CAM_DEF_FOC_X;	
	instance->focalPoint.y = CAM_DEF_FOC_Y;
	instance->focalPoint.z = CAM_DEF_FOC_Z;
	instance->position.x = CAM_DEF_LOC_X;
	instance->position.y = CAM_DEF_LOC_Y;
	instance->position.z = CAM_DEF_LOC_Z;
	instance->upDirection.x = CAM_DEF_UP_X;
	instance->upDirection.y = CAM_DEF_UP_Y;
	instance->upDirection.z = CAM_DEF_UP_Z;
	return instance;
}
