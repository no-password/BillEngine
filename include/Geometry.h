#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H

#include "common.h"
#include <cmath>

typedef struct point3d {
	GLfloat x, y, z;
} Point3D;


GLfloat distance(const Point3D* p, const Point3D* q);

typedef struct point2d {
	GLfloat x, y;
} Point2D;

//GLfloat distance(const Point2D* p, const Point2D* q);
#endif
