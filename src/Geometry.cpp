#include "Geometry.h"
#include <cmath>
#include <iostream>

GLfloat distance(const Point3D* p, const Point3D* q) {
	return (GLfloat) sqrt( (p->x * p->x - q->x * q->x) + (p->y * p->y - q->y * q->y) + (p->z * p->z - q->z * q->z) );
}

GLfloat distance(const Point2D* p, const Point2D* q) {
	return (GLfloat) sqrt( (p->x * p->x - q->x * q->x) + (p->y * p->y - q->y * q->y) );
}

void printPoint(const Point3D p) {
	std::cout << "X: " << p.x << "\nY " << p.y << "\nZ: " << p.z << std::endl;
}

void rotate(const Point3D* fixed, Point3D* target, double theta, Dimension dim) {		switch (dim) {
		case X:
			target->x -= fixed->x;
			target->z -= fixed->z;
			target->x = target->z * sin( d2r(theta) ) + target->x * cos( d2r(theta) );
			target->z = target->z * cos( d2r(theta) ) - target->x * sin( d2r(theta) );
			target->x += fixed->x;
			target->z += fixed->z;
			break;
		case Y:
			break; //TODO: impliment
		case Z:
			break; //TODO: impliment
	}	
}
