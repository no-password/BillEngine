#include "Camera.h"

static Camera* instance = nullptr;

static void setCameraFirstPersonDefault() {
	instance->focalPoint.x = CAM_DEF_FOC_X;
	instance->focalPoint.y = CAM_DEF_FOC_Y;
	instance->focalPoint.z = CAM_DEF_FOC_Z;
	instance->position.x = CAM_DEF_LOC_X;
	instance->position.y = CAM_DEF_LOC_Y;
	instance->position.z = CAM_DEF_LOC_Z;
	instance->upDirection.x = CAM_DEF_UP_X;
	instance->upDirection.y = CAM_DEF_UP_Y;
	instance->upDirection.z = CAM_DEF_UP_Z;
}

Camera* Camera::getCamera() {
	if (instance == nullptr) {
		instance = new Camera();
	}

	setCameraFirstPersonDefault();

	return instance;
}


void Camera::lookFirstPerson() {
	setCameraFirstPersonDefault();
}


void Camera::lookTopDown() {
	instance->focalPoint.x = 0;	
	instance->focalPoint.y = 0;
	instance->focalPoint.z = 0;
	instance->position.x = 0;
	instance->position.y = 1.0f;
	instance->position.z = 0;
	instance->upDirection.x = 1.0f;
	instance->upDirection.y = 0.0f;
	instance->upDirection.z = 0.0f;
}

