#include "Camera.h"
#include "Geometry.h"
#include <cmath>

static Camera* instance_Camera = nullptr;

static void setCameraFirstPersonDefault() {
	instance_Camera->focalPoint.x = CAM_DEF_FOC_X;
	instance_Camera->focalPoint.y = CAM_DEF_FOC_Y;
	instance_Camera->focalPoint.z = CAM_DEF_FOC_Z;
	instance_Camera->position.x = CAM_DEF_LOC_X;
	instance_Camera->position.y = CAM_DEF_LOC_Y;
	instance_Camera->position.z = CAM_DEF_LOC_Z;
	instance_Camera->upDirection.x = CAM_DEF_UP_X;
	instance_Camera->upDirection.y = CAM_DEF_UP_Y;
	instance_Camera->upDirection.z = CAM_DEF_UP_Z;
}

Camera* Camera::getCamera() {
	if (instance_Camera == nullptr) {
		instance_Camera = new Camera();
		setCameraFirstPersonDefault();
	}

	return instance_Camera;
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
	instance_Camera->focalPoint.x = 0;	
	instance_Camera->focalPoint.y = 0;
	instance_Camera->focalPoint.z = 0;
	instance_Camera->position.x = 0;
	instance_Camera->position.y = 1.0f;
	instance_Camera->position.z = 0;
	instance_Camera->upDirection.x = 1.0f;
	instance_Camera->upDirection.y = 0.0f;
	instance_Camera->upDirection.z = 0.0f;
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
					instance_Camera->position.y += 0.05f;
					instance_Camera->focalPoint.y += 0.05f;
					break;
				case (GLFW_KEY_LEFT_SHIFT):
					if (instance_Camera->position.y > CAM_DEF_LOC_Y + 0.05f) { 
						instance_Camera->position.y -= 0.05f;
						instance_Camera->focalPoint.y -= 0.05f;
					}
					break;
			}
		}
	}
}

void Camera::rotateFocalPointAboutPositionHorizontal(double angle) {
	rotate(&position, &focalPoint, angle, AXIS_Y);
	this->angleHorizontal += angle;
}

void Camera::rotateFocalPointAboutPositionVertical(double angle) {
	if ((angle < 0 && angleVertical > -MAX_VERT_ANGLE) ||
	(angle > 0 && angleVertical < MAX_VERT_ANGLE)) {	
		rotate(&position, &focalPoint, angle, AXIS_X);
		this->angleVertical += angle;
	}
}

void Camera::moveForwardRelative(double velocity) {
	position.z -= velocity * cos(d2r(angleHorizontal));
	position.x -= velocity * sin(d2r(angleHorizontal));
	focalPoint.z -= velocity * cos(d2r(angleHorizontal));
	focalPoint.x -= velocity * sin(d2r(angleHorizontal));
}

void Camera::moveBackwardRelative(double velocity) {
	position.z += velocity * cos(d2r(angleHorizontal));
	position.x += velocity * sin(d2r(angleHorizontal));
	focalPoint.z += velocity * cos(d2r(angleHorizontal));
	focalPoint.x += velocity * sin(d2r(angleHorizontal));
}

void Camera::moveLeftRelative(double velocity) {
	position.z += velocity * sin(d2r(angleHorizontal));
	position.x -= velocity * cos(d2r(angleHorizontal));
	focalPoint.z += velocity * sin(d2r(angleHorizontal));
	focalPoint.x -= velocity * cos(d2r(angleHorizontal));
}

void Camera::moveRightRelative(double velocity) {
	position.z -= velocity * sin(d2r(angleHorizontal));
	position.x += velocity * cos(d2r(angleHorizontal));
	focalPoint.z -= velocity * sin(d2r(angleHorizontal));
	focalPoint.x += velocity * cos(d2r(angleHorizontal));
}
