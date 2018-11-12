#include "Geometry.h"
#include <cmath>

GLfloat distance(const Point3D* p, const Point3D* q) {
	return (GLfloat) sqrt( (p->x * p->x - q->x * q->x) + (p->y * p->y - q->y * q->y) + (p->z * p->z - q->z * q->z) );
}
/*
GLfloat distance(const Point2D* p, const Point2D* q) {
	return (GLfloat) sqrt( (p->x * p->x - q->x * q->x) + (p->y * p->y - q->y * q->y) );
}*/
