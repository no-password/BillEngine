#include "Geometry.h"
#include <cmath>
#include <iostream>

/* Point3D ======================================================== */
GLfloat distance(const Point3D* p, const Point3D* q) {
	return (GLfloat) sqrt( (p->x * p->x - q->x * q->x) + (p->y * p->y - q->y * q->y) + (p->z * p->z - q->z * q->z) );
}

void printPoint(const Point3D p) {
	std::cout << "X: " << p.x << "\nY " << p.y << "\nZ: " << p.z << std::endl;
}

/**
 * Translates the target point to around the origin where fixed would be the origin,
 * rotates about the origin depending on which axis was specified, translates point back
 * to appropriate position.
 */
void rotate(const Point3D* fixed, Point3D* target, double theta, Axis axis) {		switch (axis) {
		case AXIS_Y:
			target->x -= fixed->x;
			target->z -= fixed->z;
			target->x = target->z * sin( d2r(theta) ) + target->x * cos( d2r(theta) );
			target->z = target->z * cos( d2r(theta) ) - target->x * sin( d2r(theta) );
			target->x += fixed->x;
			target->z += fixed->z;
			break;
		case AXIS_X:
			break; //TODO: impliment
		case AXIS_Z:
			break; //TODO: impliment
	}	
}

/* Point2D ============================================================ */
GLfloat distance(const Point2D* p, const Point2D* q) {
	return (GLfloat) sqrt( (p->x * p->x - q->x * q->x) + (p->y * p->y - q->y * q->y) );
}

