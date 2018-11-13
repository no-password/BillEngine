#include "Camera.h"
#include "Geometry.h"
#include <cmath>

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
		setCameraFirstPersonDefault();
	}

	return instance;
}

void Camera::look() {
	gluLookAt(
		position.x, position.y, position.z,
		focalPoint.x, focalPoint.y, focalPoint.z,
		upDirection.x, upDirection.y, upDirection.z
	);
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

void Camera::moveBasedOnKeyPressMap(const std::unordered_map<int, bool>* keyPressMap /*pointer b/c do not want to copy this*/) {
	for (const auto& entry: *keyPressMap) {
		if (entry.second == true) {
			switch (entry.first) {
				case (GLFW_KEY_W):
					this->moveForwardRelative(CAMERA_VELOCITY);
					break;
				case (GLFW_KEY_S):
					this->moveBackwardRelative(CAMERA_VELOCITY);
					break;
				case (GLFW_KEY_A):
					this->moveLeftRelative(CAMERA_VELOCITY);
					break;
				case (GLFW_KEY_D):
					this->moveRightRelative(CAMERA_VELOCITY);
					break;
				case (GLFW_KEY_SPACE):
					instance->position.y += 0.05f;
					instance->focalPoint.y += 0.05f;
					break;
				case (GLFW_KEY_LEFT_SHIFT):
					if (instance->position.y > CAM_DEF_LOC_Y + 0.05f) { 
						instance->position.y -= 0.05f;
						instance->focalPoint.y -= 0.05f;
					}
					break;
			}
		}
	}
}

void Camera::rotateFocalPointAboutPositionHorizontal(double angle) {
	rotate(&position, &focalPoint, angle, AXIS_Y);
	this->angle += angle;
}

void Camera::moveForwardRelative(double velocity) {
	position.z -= velocity * cos(d2r(angle));
	position.x -= velocity * sin(d2r(angle));
	focalPoint.z -= velocity * cos(d2r(angle));
	focalPoint.x -= velocity * sin(d2r(angle));
}

void Camera::moveBackwardRelative(double velocity) {
	position.z += velocity * cos(d2r(angle));
	position.x += velocity * sin(d2r(angle));
	focalPoint.z += velocity * cos(d2r(angle));
	focalPoint.x += velocity * sin(d2r(angle));
}

void Camera::moveLeftRelative(double velocity) {
	position.z += velocity * sin(d2r(angle));
	position.x -= velocity * cos(d2r(angle));
	focalPoint.z += velocity * sin(d2r(angle));
	focalPoint.x -= velocity * cos(d2r(angle));
}

void Camera::moveRightRelative(double velocity) {
	position.z -= velocity * sin(d2r(angle));
	position.x += velocity * cos(d2r(angle));
	focalPoint.z -= velocity * sin(d2r(angle));
	focalPoint.x += velocity * cos(d2r(angle));
}
